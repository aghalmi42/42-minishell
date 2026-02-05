/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:59:43 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:41:03 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*type_conversion(va_list list, char c)
{
	if (c == 'd' || c == 'i')
		return (conversion_int(list));
	if (c == 'u')
		return (conversion_unsigned(list));
	if (c == 'x')
		return (conversion_hex(list, 0));
	if (c == 'X')
		return (conversion_hex(list, 1));
	if (c == 'p')
		return (conversion_point(list));
	if (c == '%')
		return (conversion_percent());
	if (c == 'c')
		return (conversion_char(list));
	if (c == 's')
		return (conversion_string(list));
	return (NULL);
}

char	*conversion_final(t_data *data, t_flags *flag, char c)
{
	char	*str;

	if (c == '%')
		return (ft_strdup("%"));
	str = conversion_precision(data, flag, c);
	free(data->str);
	if ((flag->zero && ((flag->space || flag->plus || data->is_neg)
				|| ((flag->hashtag || flag->space) && (c == 'x' || c == 'X'))))
		|| ((flag->width) && (data->is_char_null)))
	{
		flag->width--;
		str = manag_width(str, flag);
		str = manag_prefix(str, data, flag, c);
	}
	else
	{
		str = manag_prefix(str, data, flag, c);
		str = manag_width(str, flag);
	}
	return (str);
}

char	*conversion_precision(t_data *data, t_flags *flag, char c)
{
	char	*str;

	if (flag->dot && (flag->precision == 0)
		&& data->is_zero && (c == 'd' || c == 'i' || c == 'u'
			|| c == 'x' || c == 'X'))
		str = ft_strdup("");
	else
		str = manag_precision(data, flag, c);
	return (str);
}
