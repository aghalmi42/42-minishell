
#include "../../include/minishell.h"

int		is_a_directory(char *path)
{
	struct	stat path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	exec_main(t_node *ast, t_exec_data *data)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE)
		exec_pipe(ast, data);
	else if (ast->type == NODE_AND)
		exec_and(ast, data);
	else if (ast->type == NODE_OR)
		exec_or(ast, data);
	else if (ast->type == NODE_SUBSHELL)
		exec_subshell(ast, data);
	else if (ast->type == NODE_CMD || ast->type == NODE_REDIR)
		exec_redir_and_cmd(ast, data);
}
