
#include "../../include/minishell.h"

void	expand_token(t_token *token, t_exec_data *data)
{
	t_token	*current;
	t_token	*next;
	t_token	*prev;

	current = token;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
			process_word_token(current, prev, data);
		prev = current;
		current = next;
	}
}

/* fonction principal dexpansion */
char	*expand_value(char *str, t_exec_data *data)
{
	char	*result;
	int		var[3];

	result = gc_malloc(10000, &data->gc_head);
	if (!result)
		return (NULL);
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	case_expand(str, result, var, data);
	result[var[1]] = '\0';
	return (result);
}
