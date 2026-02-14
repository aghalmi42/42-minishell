
#include "../../include/minishell.h"

/* verif si la cmd commence par && ou || */
int	logical_start(t_token *token, t_exec_data *data)
{
	if (token->type == TOKEN_AND || token->type == TOKEN_OR)
	{
		if (token->type == TOKEN_AND)
			print_syntax_error("&&", data);
		else
			print_syntax_error("||", data);
		return (1);
	}
	return (0);
}

/* verif token suivant apres && ou || */
int	check_logical_token(t_token *token, t_exec_data *data)
{
	if (token->next == NULL)
	{
		print_syntax_error("newline", data);
		return (-1);
	}
	if (token->next->type == TOKEN_AND 
		|| token->next->type == TOKEN_OR
		|| token->next->type == TOKEN_PIPE)
	{
		if (token->next->type == TOKEN_AND)
			print_syntax_error("&&", data);
		else if (token->next->type == TOKEN_OR)
			print_syntax_error("||", data);
		else
			print_syntax_error("|", data);
		return (-1);
	}
	return (0);
}

/* verif les erreur de && et || */
int	check_syntax_logical(t_token *token, t_exec_data *data)
{
	if (logical_start(token, data))
		return (-1);
	while (token)
	{
		if (token->type == TOKEN_AND || token->type == TOKEN_OR)
		{
			if (check_logical_token(token, data) == -1)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}
