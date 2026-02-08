/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:15:05 by alex              #+#    #+#             */
/*   Updated: 2026/02/08 04:32:55 by alex             ###   ########.fr       */
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