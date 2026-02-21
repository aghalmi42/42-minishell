/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:20:14 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:20:17 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_exit(t_exec_data *data, t_node *node)
{
	int			cpt;
	long long	exit_code;
	int			error;

	cpt = 0;
	while (node->av[cpt])
		cpt++;
	ft_putendl_fd("exit", 2);
	if (cpt == 1)
		exit_with_one_arg(node, data, data->status);
	error = 0;
	exit_code = ft_atoll(node->av[1], &error);
	if (!is_valid_number(node->av[1]) || error)
		exit_msg_error(data, node->av[1], node);
	final_exit(data, cpt, exit_code);
}
