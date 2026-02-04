/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:45:43 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:42 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_conversion_manag(char const *format, int *i, va_list list)
{
	t_flags	*flag;
	t_data	*data;
	char	*res;
	int		len;

	len = 0;
	flag = new_flag();
	parse_flag(flag, format, i, list);
	data = type_conversion(list, format[*i]);
	if (!data)
		return (data_fail(flag, format[*i]));
	res = conversion_final(data, flag, format[*i]);
	final_print(flag, data, res, &len);
	return (ft_free_conversion(flag, data, res, len));
}

void	final_print(t_flags *flag, t_data *data, char *res, int *len)
{
	if (data->is_char_null && flag->width && flag->minus)
	{
		ft_putchar_fd('\0', 1);
		ft_putstr_fd(res, 1);
		*len = *len + ft_strlen(res) + 1;
	}
	else if (data->is_char_null && flag->width)
	{
		ft_putstr_fd(res, 1);
		ft_putchar_fd('\0', 1);
		*len = *len + ft_strlen(res) + 1;
	}
	else if (data->is_char_null)
	{
		ft_putchar_fd('\0', 1);
		(*len)++;
	}
	else
	{
		ft_putstr_fd(res, 1);
		*len = *len + ft_strlen(res);
	}
}

int	data_fail(t_flags *flag, char c)
{
	free(flag);
	if (c == 's')
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	else if (c == 'p')
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	return (0);
}

int	ft_free_conversion(t_flags *flag, t_data *data, char *res, int len)
{
	free(res);
	free(data);
	free(flag);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		cpt;
	va_list	list;

	i = 0;
	cpt = 0;
	if (!format)
		return (-1);
	va_start(list, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			cpt += ft_conversion_manag(format, &i, list);
		else
		{
			ft_putchar_fd(format[i], 1);
			cpt++;
		}
		i++;
	}
	va_end(list);
	return (cpt);
}
