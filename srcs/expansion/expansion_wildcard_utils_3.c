/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard_utils_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:54:05 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 10:54:07 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fill_matches(DIR *dir, char *dir_path, char *pattern, t_exec_data *data)
{
	struct dirent	*enter;
	int				i;

	i = 0;
	enter = readdir(dir);
	while (enter)
	{
		if (enter->d_name[0] != '.' && match_pattern(pattern, enter->d_name))
			if (!process_entry(enter, &i, dir_path, data))
				return (-1);
		enter = readdir(dir);
	}
	data->match[i] = NULL;
	return (0);
}

void	get_match(char *input, t_list **gc_head_cmd, t_exec_data *data)
{
	char	*dir_path;
	char	*pattern;
	DIR		*dir;

	data->match = init_match(input, &dir_path, &pattern, gc_head_cmd);
	if (!data->match)
		return ;
	dir = opendir(dir_path);
	if (!dir)
		return (gc_free_one(gc_head_cmd, dir_path), gc_free_one(gc_head_cmd,
				pattern));
	if (fill_matches(dir, dir_path, pattern, data) == -1)
	{
		closedir(dir);
		return ;
	}
	closedir(dir);
	return ;
}

/* trie les resu par ordre alpha */
void	sort_match(char **match)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (!match)
		return ;
	while (match[i])
	{
		j = i + 1;
		while (match[j])
		{
			if (ft_strncmp(match[i], match[j], 1000) > 0)
			{
				tmp = match[i];
				match[i] = match[j];
				match[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
