/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 03:35:09 by alex              #+#    #+#             */
/*   Updated: 2026/01/26 03:38:23 by alex             ###   ########.fr       */
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