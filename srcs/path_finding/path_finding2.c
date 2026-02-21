/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:23:30 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:25:45 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*path_to_find_lst(char *cmd, t_exec_data *data)
{
	char	**possible_paths;
	char	*possible_path;

	if (!cmd)
		return (perror("Command not found"), NULL);
	if (ft_strchr(cmd, '/'))
		return (it_contain_a_slash(cmd, &data->gc_head_cmd));
	possible_paths = search_path(data->envp);
	if (!possible_paths)
		return (message_error(cmd, ": No such file or directory"), NULL);
	possible_path = search_possible_path(possible_paths, cmd,
			&data->gc_head_cmd);
	if (!possible_path)
		return (free_split(possible_paths),
			message_error(cmd, ": command not found"), NULL);
	free_split(possible_paths);
	return (possible_path);
}

char	**search_path(t_list *envp)
{
	t_list	*tmp;
	t_env	*dummy;

	tmp = envp;
	while (tmp)
	{
		dummy = tmp->content;
		if (ft_strncmp(dummy->key, "PATH", 5) == 0)
			return (ft_split(dummy->value, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}
