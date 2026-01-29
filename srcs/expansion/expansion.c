
#include "../../include/minishell.h"

/* fonction qui va expand tt les token */
void	expand_token(t_token *token, char **env)
{
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			if (!single_quote(token->value))
				expand_word(token, env);
		}
		token = token->next;
	}
}

/* verifie si mot a $ et mettre variable remplacer et supp quote */
void	expand_word(t_token *token, char **env)
{
	char	*value;

	if (!dollar(token->value))
	{
		value = remove_quote(token->value);
		free(token->value);
		token->value = value;
		return ;
	}
	value = expand_value(token->value, env);
	free(token->value);
	token->value = value;
}

/* boucle pour lexpansion */
void	case_expand(char *str, char *result, int *var, char **env)
{
	while (str[var[0]])
	{
		if (str[var[0]] == '\'' || str[var[0]] == '"')
			manage_exp_quote(str[var[0]], &var[2], &var[0]);
		else if (to_expand(str, var[0], var[2]))
			var[1] += manage_variable(str, &var[0], result + var[1], env);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '?')
			var[1] += manage_exit_code(&var[0], result + var[1]);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '$')
			var[1] += manage_pid(&var[0], result + var[1]);
		else if (str[var[0]] == '$')
			copy_char(str, &var[0], result, &var[1]);
		else
			copy_char(str, &var[0], result, &var[1]);
	}
}

/* fonction principal dexpansion */
char	*expand_value(char *str, char **env)
{
	char	*result;
	int		var[3];

	result = malloc(10000);
	if (!result)
		return (NULL);
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	case_expand(str, result, var, env);
	result[var[1]] = '\0';
	return (result);
}
