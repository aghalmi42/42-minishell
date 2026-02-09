/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:24:39 by alex              #+#    #+#             */
/*   Updated: 2026/02/09 06:08:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* permet de créer le pipe nécessaire si un node_pipe est rencontré */
void	exec_pipe(t_node *node, t_exec_data *data)
{
	int	pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	pid_left = fork();
	if (pid_left == 0)
	{
		set_signal_actions_default();
		data->is_fork = 1;
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_main(node->left, data);
		exit(data->status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		set_signal_actions_default();
		close(pipe_fd[1]);
		data->is_fork = 1;
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec_main(node->right, data);
		exit(data->status);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		data->status = 128 + WTERMSIG(status);
	}
	else
		data->status = WEXITSTATUS(data->status);
	set_signal_actions();
}