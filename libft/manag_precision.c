/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:13:01 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:25 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*manag_precision(t_data *data, t_flags *flag, char c)
{
	if (!flag->dot)
		return (ft_strdup(data->str));
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (manag_precision_nb(data, flag));
	else if (c == 's')
		return (manag_precision_str(data, flag));
	return (ft_strdup(data->str));
}

char	*manag_precision_nb(t_data *data, t_flags *flag)
{
	int		zeros;
	int		i;
	char	*str;

	zeros = flag->precision - data->len;
	i = 0;
	if (zeros <= 0)
		return (ft_strdup(data->str));
	str = malloc(sizeof(char) * (flag->precision + 1));
	if (!str)
		return (NULL);
	while (i != zeros)
		str[i++] = '0';
	zeros = 0;
	while (zeros < data->len)
		str[i++] = data->str[zeros++];
	str[i] = '\0';
	return (str);
}

char	*manag_precision_str(t_data *data, t_flags *flag)
{
	char	*str;

	if (data->is_null && flag->precision <= 5)
		return (ft_strdup(""));
	if (flag->precision < data->len)
	{
		str = malloc(sizeof(char) * (flag->precision + 1));
		ft_strlcpy(str, data->str, flag->precision + 1);
		return (str);
	}
	return (ft_strdup(data->str));
}
