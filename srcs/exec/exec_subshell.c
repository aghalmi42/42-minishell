
#include "../../include/minishell.h"

void	handle_subshell_status(int status, t_exec_data *data)
{
	if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
	else
		data->status = WEXITSTATUS(status);
}

void	exec_subshell_child(t_node *node, t_exec_data *data)
{
	set_signal_actions_default();
	data->is_fork = 1;
	exec_main(node->left, data);
	free_ast(node);
	free_envp(data);
	exit(data->status);
}

void	exec_subshell(t_node *node, t_exec_data *data)
{
	pid_t	pid;
	int		status;

	if (!node || !node->left)
	{
		data->status = 0;
		return ;
	}
	pid = fork();
	if (pid < 0)
		return ((void)(perror("fork"), data->status = 1));
	if (pid == 0)
		exec_subshell_child(node, data);
	waitpid(pid, &status, 0);
	handle_subshell_status(status, data);
	set_signal_actions();
	if (node->right)
		exec_main(node->right, data);
}
