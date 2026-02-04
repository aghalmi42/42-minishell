/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:25:29 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:41:42 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*conversion_hex(va_list list, int c)
{
	t_data			*data;
	unsigned int	nb;
	int				i;

	i = 0;
	data = new_data();
	nb = (unsigned int)va_arg(list, unsigned int);
	data->str = str_hex(data, nb);
	if (!data->str)
	{
		free(data);
		return (NULL);
	}
	if (!c)
	{
		while (i < data->len)
		{
			data->str[i] = ft_tolower(data->str[i]);
			i++;
		}
	}
	return (data);
}

char	*str_hex(t_data *data, unsigned int nb)
{
	char		*str;

	if (nb == 0)
	{
		data->is_zero = 1;
		str = ft_strdup("0");
	}
	else
	{
		if (nb == 4294967295)
			str = ft_strdup("FFFFFFFF");
		else
			str = ft_htoa(nb);
	}
	data->len = ft_strlen(str);
	return (str);
}
