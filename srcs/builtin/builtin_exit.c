/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:12:14 by alex              #+#    #+#             */
/*   Updated: 2026/02/05 06:15:32 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_exit(t_exec_data *data, t_node *node)
{
	int		i;
	char	*number;
	int		cpt;
	
	cpt = 0;
	while(node->av[cpt])
		cpt++;
	if (cpt > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	if (cpt == 1)
		exit(data->status);
	i = 0;
	number = node->av[1];
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		exit(255);
	while(number[i])
	{
		if (!ft_isdigit(number[i]))
			exit(255);
		i++;
	}
	exit(ft_atoi(number));
}