/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:24:39 by alex              #+#    #+#             */
/*   Updated: 2026/01/29 08:40:41 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_pipe(t_node *node, t_exec_data *data)
{
	int	pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipe_fd) == -1)
		return ;
	pid_left = fork();
	if (pid_left == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_main(node->left, data);
		exit(data->status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec_main(node->right, data);
		exit(data->status);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &data->status, 0);
}