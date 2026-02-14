
#include "../../include/minishell.h"

/* verif tt les erreur de syntaxe */
int	check_syntax(t_token *token, t_exec_data *data)
{
	if (!token)
		return (0);
	if (check_syntax_logical(token, data) == -1)
		return (-1);
	if (check_pipe_syntax(token, data) == -1)
		return (-1);
	if (check_redir_syntax(token, data) == -1)
		return (-1);
	return (0);
}
