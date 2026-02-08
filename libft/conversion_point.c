/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:25:50 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:41:18 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*conversion_point(va_list list)
{
	t_data				*data;
	unsigned long long	nb;

	data = new_data();
	nb = (unsigned long long)va_arg(list, void *);
	data->str = str_point(data, nb);
	if (!data->str)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

char	*str_point(t_data *data, unsigned long long nb)
{
	char		*str;

	if (nb == 0)
	{
		data->is_null = 1;
		return (ft_strdup("(nil)"));
	}
	str = ft_ptoa(nb);
	data->len = ft_strlen(str);
	return (str);
}
