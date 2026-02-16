/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:52:27 by alex              #+#    #+#             */
/*   Updated: 2026/02/16 01:52:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_data	*set_t_exec_data(void)
{
	t_exec_data *data;
	
	data = malloc(sizeof(t_exec_data));
	if (!data)
		return (NULL);
}
