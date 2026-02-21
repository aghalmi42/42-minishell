/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:48:26 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:48:26 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_expanded_size(char **av, t_list **gc_head_cmd, t_exec_data *data)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (av[i])
	{
		if (have_wildcard(av[i]))
			total += process_wildcard_count(av[i], gc_head_cmd, data);
		else
			total++;
		i++;
	}
	return (total);
}

void	add_matches_to_result(char **result, int *k, char **match,
			t_list **gc_head_cmd)
{
	int	j;

	sort_match(match);
	j = 0;
	while (match[j])
	{
		result[(*k)++] = gc_strdup(match[j], gc_head_cmd);
		gc_free_one(gc_head_cmd, match[j]);
		j++;
	}
	gc_free_one(gc_head_cmd, match);
}

int	process_wildcard_match(char *arg, char **result, int *k,
			t_exec_data *data)
{
	get_match(arg, &data->gc_head_cmd, data);
	if (data->match)
	{
		add_matches_to_result(result, k, data->match, &data->gc_head_cmd);
		return (1);
	}
	return (0);
}

void	fill_result(char **result, char **av, t_list **gc_head_cmd,
			t_exec_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (av[i])
	{
		if (have_wildcard(av[i])
			&& process_wildcard_match(av[i], result, &k, data))
		{
			i++;
			continue ;
		}
		result[k++] = gc_strdup(av[i], gc_head_cmd);
		if (!result[k - 1])
			return ;
		i++;
	}
	result[k] = NULL;
}

char	**expand_wildcard(char **av, t_list **gc_head_cmd, t_exec_data *data)
{
	char	**result;
	int		total;

	if (!av)
		return (NULL);
	total = count_expanded_size(av, gc_head_cmd, data);
	result = gc_malloc(sizeof(char *) * (total + 1), gc_head_cmd);
	if (!result)
		return (NULL);
	fill_result(result, av, gc_head_cmd, data);
	return (result);
}
