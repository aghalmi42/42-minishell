
#include "../../include/minishell.h"

int	original_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	count_split_word(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

char	*extract_next_word(char *str, int *pos)
{
	int		start;
	int		len;
	char	*word;

	while (str[*pos] && (str[*pos] == ' ' || str[*pos] == '\t' || str[*pos] == '\n'))
		(*pos)++;
	if (!str[*pos])
		return (NULL);
	start = *pos;
	while (str[*pos] && str[*pos] != ' ' && str[*pos] != '\t' && str[*pos] != '\n')
		(*pos)++;
	len = *pos - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, str + start, len);
	word[len] = '\0';
	return (word);
}

void	add_word_token(t_token **last, char *word)
{
	t_token	*new_tok;

	new_tok = new_token(TOKEN_WORD, word);
	if (new_tok)
	{
		new_tok->next = (*last)->next;
		(*last)->next = new_tok;
		*last = new_tok;
	}
	free(word);
}

void	insert_split_token(t_token *current, char *expand)
{
	int		pos;
	int		word_count;
	int		i;
	char	*word;
	t_token	*last;

	word_count = count_split_word(expand);
	if (word_count == 0)
	{
		free(current->value);
		current->value = ft_strdup("");
		return ;
	}
	pos = 0;
	i = 0;
	last = current;
	while (i < word_count)
	{
		word = extract_next_word(expand, &pos);
		if (!word)
			break;
		if (i == 0)
		{
			free(current->value);
			current->value = word;
		}
		else
			add_word_token(&last, word);
		i++;
	}
}

/* fonction qui va expand tt les token */
void	expand_token(t_token *token, t_exec_data *data)
{
	t_token	*current;
	t_token	*next;
	char	*expand;
	int		a_quote;

	current = token;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
		{
			a_quote = original_quote(current->value);
			if (single_quote(current->value))
				expand = remove_quote(current->value);
			else
				expand = expand_value(current->value, data);
			if (!a_quote && expand)
			{
				insert_split_token(current, expand);
				free(expand);
			}
			else
			{
				free(current->value);
				current->value = expand;
			}
		}
		current = next;
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

int	dollar_special(char *str, int *i)
{
	if (ft_isdigit(str[*i + 1]))
	{
		(*i) += 2;
		return (1);
	}
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

/* boucle pour lexpansion */
void	case_expand(char *str, char *result, int *var, t_exec_data *data)
{
	while (str[var[0]])
	{
		if (str[var[0]] == '\'' && var[2] == 0)
		{
			var[2] = 1;
			var[0]++;
		}
		else if (str[var[0]] == '\'' && var[2] == 1)
		{
			var[2] = 0;
			var[0]++;
		}
		else if (str[var[0]] == '"' && var[2] == 0)
		{
			var[2] = 2;
			var[0]++;
		}
		else if (str[var[0]] == '"' && var[2] == 2)
		{
			var[2] = 0;
			var[0]++;
		}
		else if (to_expand(str, var[0], var[2]))
			var[1] += manage_variable(str, &var[0], result + var[1], data->envp);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '?')
			var[1] += manage_exit_code(&var[0], result + var[1], data);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '$')
			var[1] += manage_pid(&var[0], result + var[1]);
		else if (str[var[0]] == '$' && var[2] != 1)
		{
			if (dollar_special(str, &var[0]))
				continue;
			copy_char(str, &var[0], result, &var[1]);
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
