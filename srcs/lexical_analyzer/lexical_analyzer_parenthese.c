
#include "../../include/minishell.h"

/* pour gerer les parenthesse */
int  manage_parenthese(char *line, int *i, t_token **up, t_list **gc_head)
{
	t_token *token;

	if (line[*i] == '(')
	{
		token = new_token(TOKEN_LEFT_PAREN, NULL, gc_head);
		if (!token)
			return (0);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	else if (line[*i] == ')')
	{
		token = new_token(TOKEN_RIGHT_PAREN, NULL, gc_head);
		if (!token)
			return (0);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	return (0);
}
