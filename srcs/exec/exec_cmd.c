/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:46:26 by alex              #+#    #+#             */
/*   Updated: 2026/02/09 06:18:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cmd(t_node *node, t_exec_data *data)
{
	char	*path_cmd;
	char	**envp;

	if(is_a_built_in(node->av[0]))
	{
		exec_built_in(node->av[0], data, node);
		if (data->is_fork)
			exit(data->status);
		return ;
	}
	path_cmd = path_to_find_lst(node->av[0], data);
	if (!path_cmd)
	{
		data->status = 127;
		if (data->is_fork)
			exit(127);
		return ;
	}
	if (is_a_directory(path_cmd))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(path_cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		data->status = 126;
		if (data->is_fork)
			exit(126);
		return ;
	}
	envp = getenv_to_str(data->envp);
	if (!envp)
	{
		free(path_cmd);
		data->status = 1;
		if (data->is_fork)
			exit(1);
		return ;
	}
	if (execve(path_cmd, node->av, envp) == -1)
	{
		perror("execve");
		free(path_cmd);
		free_split(envp);
		exit(126);
	}
}

// void	exec_final(char *path_cmd, char **envp, t_node *node, t_exec_data *data)
// {
// 	pid_t	pid;

// 	if (!data->is_fork)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			data->status = 1;
// 		if (pid == 0)
// 		{
// 			if (execve(path_cmd, node->av, envp) == - 1)
// 			{
// 				free_split(envp);
// 				perror("execve fail");
// 				exit(126);
// 			}
// 		}
// 		waitpid(pid, &data->status, 0);
// 		return ;
// 	}
// 	if (execve(path_cmd, node->av, envp) == - 1)
// 	{
// 		perror("execve fail");
// 		free_split(envp);
// 		data->status = 126;
// 		return ;
// 	}
// }


void	exec_built_in(char *cmd, t_exec_data *data, t_node *node)
{
	if (!ft_strncmp("env", cmd, 4))
		return(builtin_env(data,node, 0));
	else if (!ft_strncmp("export", cmd, 7))
		return (builtin_export(data, node));
	else if (!ft_strncmp("unset", cmd, 6))
		return (builtin_unset(data, node));
	else if (!ft_strncmp("exit", cmd, 5))
		return (builtin_exit(data, node));
	else if (!ft_strncmp("echo", cmd, 5))
		return (builtin_echo(node->av, data));
	else if (!ft_strncmp("cd", cmd, 3))
		return (builtin_cd(data, node));
	else if (!ft_strncmp("pwd", cmd, 4))
		return (builtin_pwd(data, node));
}

int	is_a_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd, 5))
		return (1);
	else if (!ft_strncmp("cd", cmd, 3))
		return (1);
	else if (!ft_strncmp("pwd", cmd, 4))
		return (1);
	else if (!ft_strncmp("export", cmd, 7))
		return (1);
	else if (!ft_strncmp("unset", cmd, 6))
		return (1);
	else if (!ft_strncmp("env", cmd, 4))
		return (1);
	else if (!ft_strncmp("exit", cmd, 5))
		return (1);
	return (0);
}

char	**getenv_to_str(t_list *envp)
{
	char	**env;
	int		i;
	int		j;

	i = envp_count(envp);
	env = malloc(sizeof (char *) * (i + 1));
	if (!env)
		return (NULL);
	j = 0;
	while (j != i)
	{
		env[j] = envp_value(envp->content);
		if (!env[j])
			return (free_split(env), NULL);
		j++;
		envp = envp->next;
	}
	env[j] = NULL;
	return (env);
}

char	*envp_value(t_env *content)
{
	char	*tmp;
	char	*value;

	tmp = ft_strjoin(content->key, "=");
	if(!tmp)
		return (NULL);
	value = ft_strjoin(tmp, content->value);
	if (!value)
		return(free(tmp), NULL);
	free(tmp);
	return (value);
}

int		envp_count(t_list *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		envp = envp->next;
		i++;
	}
	return (i);
}
