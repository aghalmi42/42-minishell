/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:32:31 by amoderan          #+#    #+#             */
/*   Updated: 2026/02/04 06:44:54 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    built_in_env(t_exec_data *data)
{
    t_list  *dummy;
    t_env   *e;
    
    dummy = data->envp;
    while(dummy)
    {
        e = dummy->content;
        ft_putstr_fd(e->key, STDOUT_FILENO);
        ft_putstr_fd("=", STDOUT_FILENO);
        ft_putstr_fd(e->value, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        dummy = dummy->next;
    }
}

void    built_in_export(t_exec_data *data)
{
    
}

void    built_in_unset(t_exec_data *data)
{

}

void    built_in_exit(t_exec_data *data)
{
    
}