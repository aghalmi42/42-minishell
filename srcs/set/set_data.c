/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:46:59 by amoderan          #+#    #+#             */
/*   Updated: 2026/02/12 04:50:14 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_data    *set_t_exec_data(void)
{
    t_exec_data *data;
    
    data = malloc(sizeof(t_exec_data));
    if (!data)
        return (NULL);
    
}