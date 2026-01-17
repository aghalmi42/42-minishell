
#include "../../include/minishell.h"

/* pour trv la 1er pipe dans la lst de token */
t_token	*search_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/* pour trv la 1er redirection dans la lst de token */
t_token	*search_redir(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
			return (token);
		token = token->next;
	}
	return (NULL);
}
