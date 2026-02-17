

#include "../../include/minishell.h"

char	*handle_heredoc_expand(char *value, int *a_quote, t_list **gc_head)
{
	char	*expand;
	char	*tmp;

	*a_quote = original_quote(value);
	expand = remove_quote(value, gc_head);
	if (!expand)
		return (NULL);
	if (*a_quote)
	{
		tmp = gc_strjoin("\x01", expand, gc_head);
		if (!tmp)
			return (NULL);
		gc_free_one(gc_head, expand);
		expand = tmp;
	}
	return (expand);
}

char	*handle_normal_expand(char *value, int *a_quote, t_exec_data *data)
{
	char	*expand;

	*a_quote = original_quote(value);
	if (single_quote(value))
		expand = remove_quote(value, &data->gc_head);
	else
		expand = expand_value(value, data);
	return (expand);
}

void	process_expand(t_token *current, char *expand, int a_quote, t_list **gc_head)
{
	char	*tmp;

	if (!a_quote && expand)
	{
		insert_split_token(current, expand, gc_head);
		gc_free_one(gc_head, expand);//free(expand);
	}
	else
	{
		if (a_quote && expand)
		{
			tmp = gc_strjoin("\x02", expand, gc_head);
			gc_free_one(gc_head, expand);//free(expand);
			expand = tmp;
		}
		gc_free_one(gc_head, current->value);//free(current->value);
		current->value = expand;
	}
}

void	process_word_token(t_token *current, t_token *prev, t_exec_data *data)
{
	char	*expand;
	int		a_quote;

	if (prev && prev->type == TOKEN_HEREDOC)
	{
		expand = handle_heredoc_expand(current->value, &a_quote, &data->gc_head);
		gc_free_one(&data->gc_head, current->value); //free(current->value);
		current->value = expand;
	}
	else
	{
		expand = handle_normal_expand(current->value, &a_quote, data);
		process_expand(current, expand, a_quote, &data->gc_head);
	}
}
