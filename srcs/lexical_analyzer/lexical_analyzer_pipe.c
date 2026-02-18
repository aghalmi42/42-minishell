
#include "../../include/minishell.h"

/* on gere la pipe */
int	manage_pipe(char *line, int *i, t_token **up, t_list **gc_head)
{
	t_token	*token;

	if (line[*i] == '|')
	{
		token = new_token(TOKEN_PIPE, NULL, gc_head);
		if (!token)
			return (-1);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	return (0);
}
