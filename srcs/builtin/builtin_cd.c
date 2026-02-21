/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:14:11 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:14:11 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_cd(t_exec_data *data, t_node *node)
{
	char	*path;

	if (node->av[1] && node->av[2])
		return ((void)handle_cd_error(NULL, data, "cd : too many argument"));
	path = search_cd_path(data, node);
	if (!path)
	{
		data->status = 1;
		return ;
	}
	if (!path[0])
		return ;
	execute_cd(path, data);
}
