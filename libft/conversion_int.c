/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:25:44 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:41:33 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*conversion_int(va_list list)
{
	t_data	*data;
	int		nb;

	data = new_data();
	nb = (int)va_arg(list, int);
	data->str = str_int(data, nb);
	if (!data->str)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

char	*str_int(t_data *data, int nb)
{
	char				*str;
	unsigned int		n;

	if (nb == 0)
		data->is_zero = 1;
	if (nb < 0)
	{
		data->is_neg = 1;
		if (nb == -2147483648)
			str = ft_strdup("2147483648");
		else
		{
			n = (unsigned int)-nb;
			str = ft_itoa(n);
		}
	}
	else
		str = ft_itoa(nb);
	data->len = ft_strlen(str);
	return (str);
}

t_data	*conversion_unsigned(va_list list)
{
	t_data			*data;
	unsigned int	nb;

	data = new_data();
	nb = (unsigned int)va_arg(list, unsigned int);
	data->str = str_unsigned(data, nb);
	if (!data->str)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

char	*str_unsigned(t_data *data, unsigned int nb)
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
			str = ft_strdup("4294967295");
		else
			str = ft_utoa(nb);
	}
	data->len = ft_strlen(str);
	return (str);
}
