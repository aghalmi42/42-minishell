/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:34:12 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 10:13:59 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_args_markers(char **av)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (!av)
		return ;
	i = 0;
	while (av[i])
	{
		str = av[i];
		j = 0;
		k = 0;
		while (str[j])
		{
			if (str[j] != 2)
			{
				str[k] = str[j];
				k++;
			}
			j++;
		}
		str[k] = '\0';
		i++;
	}
}

void	exec_cmd(t_node *node, t_exec_data *data)
{
	char	**expand_av;

	if (!node->av || !node->av[0] || node->av[0][0] == '\0')
	{
		data->status = 0;
		if (data->is_fork)
		{
			gc_delete(&data->gc_head_cmd);
			gc_delete(&data->gc_head_env);
			exit(0);
		}
		return ;
	}
	expand_av = expand_wildcard(node->av, &data->gc_head_cmd, data);
	if (expand_av)
		node->av = expand_av;
	clean_args_markers(node->av);
	if (is_a_built_in(node->av[0]))
	{
		handle_builtin(node, data);
		return ;
	}
	run_external_cmd(node, data);
}
