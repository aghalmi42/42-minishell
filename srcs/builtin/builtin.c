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

int	builtin_cd(t_exec_data *data, t_node *node)
{
	char	*path;
	int		ret;
	char	*old_path;

	path = search_cd_path(node->av, data->envp);
	if (!path)
		return (0);
	ret = change_directory(path);
	free(path);
	return (ret);
}

char *search_home_path(t_exec_data *data)
{
	char *path;

	path = find_home_value(data, data->envp);
	if (!path)
		ft_putendl_fd("cd : HOME is not set", 2);
	return (path);
}

char	*find_home_value(t_exec_data *data, t_list *envp)
{
	t_list	*cur;
	t_env	*env;
	char	*home;

	cur = envp;
	while (cur)
	{
		env = cur->content;
		if (!ft_strncmp(env->key, "HOME", 5))
		{
			home = ft_strdup(env->value);
			if (!home)
			{
				data->status = 1;
				return (NULL);
			}
			return (home);
		}
		cur = cur->next;
	}
	return (NULL);
}

/* recupere le chemin OLDPWD et lafficher */
char *search_oldpwd_path(t_exec_data *data, t_list *envp)
{
	t_list	*cur;
	t_env	*env;
	char	*oldpwd;

	cur = envp;
	while (cur)
	{
		env = cur->content;
		if (!ft_strncmp(env->key, "OLDPWD", 7))
		{
			oldpwd = ft_strdup(env->value);
			if (!oldpwd)
			{
				data->status = 1;
				return (NULL);
			}
			return (oldpwd);
		}
		cur = cur->next;
	}
	return (NULL);
}

/* on va determiner le chemin de la dest */
char *search_cd_path(t_exec_data *data, t_node *node)
{
	if (!node->av[1])
		return (search_home_path(data));
	else if (ft_strncmp(node->av[1], "-", 2) == 0 && node->av[1][1] == '\0')
		return (search_oldpwd_path(data, data->envp));
	else
		return (ft_strdup(node->av[1]));
}