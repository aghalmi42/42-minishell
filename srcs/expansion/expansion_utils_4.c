

#include "../../include/minishell.h"

char	*handle_heredoc_expand(char *value, int *a_quote)
{
	char	*expand;
	char	*tmp;

	*a_quote = original_quote(value);
	expand = remove_quote(value);
	if (*a_quote)
	{
		tmp = ft_strjoin("\x01", expand);
		free(expand);
		expand = tmp;
	}
	return (expand);
}

char	*handle_normal_expand(char *value, int *a_quote, t_exec_data *data)
{
	char	*expand;

	*a_quote = original_quote(value);
	if (single_quote(value))
		expand = remove_quote(value);
	else
		expand = expand_value(value, data);
	return (expand);
}

void	process_expand(t_token *current, char *expand, int a_quote)
{
	char	*tmp;

	if (!a_quote && expand)
	{
		insert_split_token(current, expand);
		free(expand);
	}
	else
	{
		if (a_quote && expand)
		{
			tmp = ft_strjoin("\x02", expand);
			free(expand);
			expand = tmp;
		}
		free(current->value);
		current->value = expand;
	}
}

void	process_word_token(t_token *current, t_token *prev, t_exec_data *data)
{
	char	*expand;
	int		a_quote;

	if (prev && prev->type == TOKEN_HEREDOC)
	{
		expand = handle_heredoc_expand(current->value, &a_quote);
		free(current->value);
		current->value = expand;
	}
	else
	{
		expand = handle_normal_expand(current->value, &a_quote, data);
		process_expand(current, expand, a_quote);
	}
}
