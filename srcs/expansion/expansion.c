
#include "../../include/minishell.h"

/* fonction qui va expand tt les token */
void	expand_token(t_token *token, t_exec_data *data)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
			expand_word(token, data);
		token = token->next;
	}
}

/* verifie si mot a $ et mettre variable remplacer et supp quote */
void	expand_word(t_token *token, t_exec_data *data)
{
	char	*value;

	if (single_quote(token->value))
	{
		value = remove_quote(token->value);
		free(token->value);
		token->value = value;
		return ;
	}
	value = expand_value(token->value, data);
	free(token->value);
	token->value = value;
}

/* boucle pour lexpansion */
void	case_expand(char *str, char *result, int *var, t_exec_data *data)
{
	while (str[var[0]])
	{
		if (str[var[0]] == '\'' || str[var[0]] == '"')
		{
			var[0]++;
			continue ;
		}
		else if (to_expand(str, var[0], var[2]))
			var[1] += manage_variable(str, &var[0], result + var[1], data->envp);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '?')
			var[1] += manage_exit_code(&var[0], result + var[1], data);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '$')
			var[1] += manage_pid(&var[0], result + var[1]);
		else if (str[var[0]] == '$')
		{
			if (str[var[0] + 1] == ' ' || str[var[0] + 1] == '\0' || str[var[0] + 1] == '\'' || str[var[0] + 1] == '"')
				copy_char(str, &var[0], result, &var[1]);
			else
				var[0]++;
		}
		else
			copy_char(str, &var[0], result, &var[1]);
	}
}

/* fonction principal dexpansion */
char	*expand_value(char *str, t_exec_data *data)
{
	char	*result;
	int		var[3];

	result = malloc(10000);
	if (!result)
		return (NULL);
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	case_expand(str, result, var, data);
	result[var[1]] = '\0';
	return (result);
}
