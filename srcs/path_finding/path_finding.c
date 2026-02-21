/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:12:52 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:48:10 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_possible_path(char *cmd, char *folder)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(folder, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	if (!path)
		return (free(tmp), NULL);
	free(tmp);
	return (path);
}

char	*it_contain_a_slash(char *cmd, t_list **gc_head_cmd)
{
	if (!access(cmd, F_OK))
		return (gc_strdup(cmd, gc_head_cmd));
	return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd, 2),
		ft_putendl_fd(": No such file or directory", 2), NULL);
}

char	*path_to_find(char *cmd, char **envp, t_list **gc_head_cmd)
{
	char	**possible_paths;
	char	*possible_path;
	int		i;
	int		nb_env;

	i = 0;
	if (!cmd)
		return (perror("Command not found"), NULL);
	if (ft_strchr(cmd, '/'))
		return (it_contain_a_slash(cmd, gc_head_cmd));
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	nb_env = count_env(envp);
	if (i == nb_env)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd, 2),
			ft_putendl_fd(": No such file or directory", 2), NULL);
	possible_paths = ft_split(envp[i] + 5, ':');
	if (!possible_paths)
		return (gc_delete(gc_head_cmd),
			message_error(cmd, "No such file or directory"), NULL);
	possible_path = search_possible_path(possible_paths, cmd, gc_head_cmd);
	if (!possible_path)
		return (free_split(possible_paths), perror("Command not found"), NULL);
	free_split(possible_paths);
	return (possible_path);
}

char	*search_possible_path(char **possible_paths, char *cmd,
		t_list **gc_head_cmd)
{
	int		i;
	char	*possible_path;

	i = 0;
	while (possible_paths[i])
	{
		possible_path = join_possible_path(cmd, possible_paths[i]);
		if (!possible_path)
			return (NULL);
		if (!access(possible_path, F_OK))
			return (gc_add_back(gc_head_cmd, possible_path), possible_path);
		free(possible_path);
		i++;
	}
	return (NULL);
}

void	message_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
}
