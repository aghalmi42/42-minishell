/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 03:35:09 by alex              #+#    #+#             */
/*   Updated: 2026/02/03 21:15:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_one_cmd(t_node *node, char **envp)
{
	char	*path_cmd;

	path_cmd = path_to_find(node->av[0], envp);
	if (!path_cmd)
		return ;
	if (fork() == 0)
	{
		if (execve(path_cmd, node->av, envp) == - 1)
		{
			perror("execve fail");
			exit(126);
		}
	}
	wait(NULL);
	free(path_cmd);
}

void	exec_one_cmd_lst(t_node *node, t_exec_data *data)
{
	char	*path_cmd;
	char	**envp;
	pid_t	pid;
	struct sigaction	sa_default;

	if (is_a_built_in(node->av[0]))
	{
		data->status = exec_built_in(node->av[0], data);
		return ;
	}
	path_cmd = path_to_find_lst(node->av[0], data);
	if (!path_cmd)
	{
		data->status = 127;
		return ;
	}
	envp = getenv_to_str(data->envp);
	if (!envp)
		return (free(path_cmd));
	pid = fork();
	if (pid == 0)
	{
		sigaction(SIGINT, &sa_default, NULL);
		sigaction(SIGQUIT, &sa_default, NULL);
		if (execve(path_cmd, node->av, envp) == - 1)
		{
			perror("execve fail");
			exit(126);
		}
	}
	waitpid(pid, &data->status, 0);
	free(path_cmd);
	free_split(envp);
	set_signal_actions();
}