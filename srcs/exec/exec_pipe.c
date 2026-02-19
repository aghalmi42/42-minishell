
#include "../../include/minishell.h"

void	exec_pipe_left(t_node *node, int pipe_fd[2], t_exec_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	data->is_fork = 1;
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exec_main(node->left, data);
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
	exit(data->status);
}

void	exec_pipe_right(t_node *node, int pipe_fd[2], t_exec_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[1]);
	data->is_fork = 1;
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	exec_main(node->right, data);
	gc_delete(&data->gc_head_env);
	gc_delete(&data->gc_head_cmd);
	exit(data->status);
}

void	handle_pipe_status(int status, t_exec_data *data)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		data->status = 128 + WTERMSIG(status);
	}
	else
		data->status = WEXITSTATUS(status);
}

void	exec_pipe(t_node *node, t_exec_data *data)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid_left = fork();
	if (pid_left == 0)
		exec_pipe_left(node, pipe_fd, data);
	pid_right = fork();
	if (pid_right == 0)
		exec_pipe_right(node, pipe_fd, data);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	handle_pipe_status(status, data);
	set_signal_actions();
}
