
#include "../../include/minishell.h"

/* on check les erreur de syntax non valide des pipe */
int	check_pipe_syntax(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		return (-1);
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			if (token->next == NULL)
				return (-1);
			if (token->next->type == TOKEN_PIPE)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}

/* on check les erreur de syntax non valide des redirection */
int	check_redir_syntax(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			if (token->next == NULL)
				return (-1);
			if (token->next->type == !TOKEN_WORD)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}
