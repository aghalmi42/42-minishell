/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:11:35 by alex              #+#    #+#             */
/*   Updated: 2026/02/05 06:15:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_env(t_exec_data *data, int export)
{
	t_list  *dummy;
	t_env   *e;
	
	dummy = data->envp;
	while(dummy)
	{
		e = dummy->content;
		if (e->value)
			print_env(e, export);
		dummy = dummy->next;
	}
}

void	print_env(t_env *e, int export)
{
	if (export)
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(e->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(e->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(e->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(e->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}