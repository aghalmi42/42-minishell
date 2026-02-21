/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:36:42 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:36:43 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_and(t_node *node, t_exec_data *data)
{
	exec_main(node->left, data);
	if (data->status == 0)
		exec_main(node->right, data);
}

void	exec_or(t_node *node, t_exec_data *data)
{
	exec_main(node->left, data);
	if (data->status != 0)
		exec_main(node->right, data);
}
