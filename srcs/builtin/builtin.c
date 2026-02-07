/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:08:06 by alex              #+#    #+#             */
/*   Updated: 2026/02/05 06:08:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on verif si la cmd est builtin*/
int builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "pwd", 4) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0 && cmd[2] == '\0')
		return (1);
	return (0);
}

/* on exec le builtin*/
// int exec_builtin(char **av, char **env)
// {
// 	if (!av || !av[0])
// 		return (1);
// 	if (ft_strncmp(av[0], "pwd", 4) == 0 && av[0][3] == '\0')
// 		return (builtin_pwd());
// 	if (ft_strncmp(av[0], "echo", 5) == 0 && av[0][4] == '\0')
// 		return (builtin_echo(av));
// 	if (ft_strncmp(av[0], "cd", 3) == 0 && av[0][2] == '\0')
// 		return (builtin_cd(av, env));
// 	return (1);
// }

