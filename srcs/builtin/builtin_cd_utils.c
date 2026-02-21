/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:13:57 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:13:57 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* change de repertoire */
int	change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

int	handle_cd_error(char *path, t_exec_data *data, char *msg)
{
	(void)path;
	if (msg)
		ft_putendl_fd(msg, 2);
	data->status = 1;
	return (1);
}

int	execute_cd(char *path, t_exec_data *data)
{
	char	new_path[PATH_MAX];

	if (change_directory(path))
	{
		data->status = 1;
		return (1);
	}
	if (getcwd(new_path, sizeof(new_path)) == NULL)
	{
		perror("getcwd");
		data->status = 1;
		return (1);
	}
	change_env_directory(new_path, data);
	data->status = 0;
	return (0);
}

void	update_pwd(t_env *e, char *new_p, t_exec_data *data)
{
	(void)data;
	e->value = new_p;
}

void	update_oldpwd(t_env *e, char *old_path, t_exec_data *data)
{
	(void)data;
	e->value = old_path;
}
