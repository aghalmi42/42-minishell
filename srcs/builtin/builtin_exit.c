/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:12:14 by alex              #+#    #+#             */
/*   Updated: 2026/02/14 20:43:39 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_exit(t_exec_data *data, t_node *node)
{
	int		i;
	char	*number;
	int		cpt;
	int exit_code;
	
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
	{
		exit_code = data->status;
		data->status = exit_code;
		exit(exit_code);
	}
	i = 0;
	number = node->av[1];
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
	{
		ft_putstr_fd("exit : argument numeric is required\n", 2);
		data->status = 2;
		exit(2);
	}
	while(number[i])
	{
		if (!ft_isdigit(number[i]))
		{
			ft_putstr_fd("exit : argument numeric is required\n", 2);
			data->status = 2;
			exit(2);
		}
		i++;
	}
	exit_code = ft_atoi(number);
	data->status = exit_code;
	exit(exit_code);
}