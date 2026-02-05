/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:24:39 by alex              #+#    #+#             */
/*   Updated: 2026/02/05 05:45:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* permet de créer le pipe nécessaire si un node_pipe est rencontré */
void	exec_pipe(t_node *node, t_exec_data *data)
{
	int	pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	struct sigaction	sa_default;

	if (pipe(pipe_fd) == -1)
		return ;
	pid_left = fork();
	ft_memset(&sa_default, 0, sizeof(sa_default));
	sa_default.sa_handler = SIG_DFL;
	if (pid_left == 0)
	{
		sigaction(SIGINT, &sa_default, NULL);
		sigaction(SIGQUIT, &sa_default, NULL);
		data->is_pipe = 1;
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_main(node->left, data);
		exit(data->status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		sigaction(SIGINT, &sa_default, NULL);
		sigaction(SIGQUIT, &sa_default, NULL);
		close(pipe_fd[1]);
		data->is_pipe = 1;
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec_main(node->right, data);
		exit(data->status);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &data->status, 0);
	if (WIFSIGNALED(data->status))
		data->status = 128 + WTERMSIG(data->status);
	else
		data->status = WEXITSTATUS(data->status);
	set_signal_actions();
}