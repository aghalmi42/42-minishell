/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:38:38 by alex              #+#    #+#             */
/*   Updated: 2026/01/26 02:39:10 by alex             ###   ########.fr       */
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

static char	*it_contain_a_slash(char *cmd)
{
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	return (perror("Command not found"), NULL);
}

char	*path_to_find(char *cmd, char **envp)
{
	char	**possible_paths;
	char	*possible_path;
	int		i;
	int		nb_env;

	i = 0;
	if (!cmd)
		return (perror("Command not found"), NULL);
	if (ft_strchr(cmd, '/'))
		return (it_contain_a_slash(cmd));
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	nb_env = count_env(envp);
	if (i == nb_env)
		return (perror("No such file or directory"), NULL);
	possible_paths = ft_split(envp[i] + 5, ':');
	if (!possible_paths)
		return (perror("No such file or directory"), NULL);
	i = 0;
	possible_path = search_possible_path(possible_paths, cmd);
	if (!possible_path)
		return (free_split(possible_paths), perror("Command not found"), NULL);
	free_split(possible_paths);
	return (possible_path);
}

char	*search_possible_path(char **possible_paths, char *cmd)
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
			return (possible_path);
		free(possible_path);
		i++;
	}
	return (NULL);
}