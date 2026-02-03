/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 03:35:09 by alex              #+#    #+#             */
/*   Updated: 2026/02/03 02:04:35 by amoderan         ###   ########.fr       */
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

	if (is_a_built_in(node->av[0]))
		exit(exec_built_in(node->av[0]));
	path_cmd = path_to_find_lst(node->av[0], data);
	if (!path_cmd)
		return ;
	envp = getenv_to_str(data->envp);
	if (!envp)
		return (free(path_cmd));
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