
#include "../../include/minishell.h"

/* verif si la cmd commence par && ou || */
int	logical_start(t_token *token)
{
	if (token->type == TOKEN_AND || token->type == TOKEN_OR)
	{
		if (token->type == TOKEN_AND)
			print_syntax_error("&&");
		else
			print_syntax_error("||");
		return (1);
	}
	return (0);
}

/* verif token suivant apres && ou || */
int	check_logical_token(t_token *token)
{
	if (token->next == NULL)
	{
		print_syntax_error("newline");
		return (-1);
	}
	if (token->next->type == TOKEN_AND 
		|| token->next->type == TOKEN_OR
		|| token->next->type == TOKEN_PIPE)
	{
		if (token->next->type == TOKEN_AND)
			print_syntax_error("&&");
		else if (token->next->type == TOKEN_OR)
			print_syntax_error("||");
		else
			print_syntax_error("|");
		return (-1);
	}
	return (0);
}

/* verif les erreur de && et || */
int	check_syntax_logical(t_token *token)
{
	if (logical_start(token))
		return (-1);
	while (token)
	{
		if (token->type == TOKEN_AND || token->type == TOKEN_OR)
		{
			if (check_logical_token(token) == -1)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}
