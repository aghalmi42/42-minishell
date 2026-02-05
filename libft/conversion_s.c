/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:25:54 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:41:09 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*conversion_char(va_list list)
{
	t_data			*data;
	unsigned char	c;

	data = new_data();
	c = (unsigned char)va_arg(list, int);
	data->str = malloc(2);
	if (!data->str)
	{
		free(data);
		return (NULL);
	}
	if (c == 0)
		data->is_char_null = 1;
	data->str[0] = c;
	data->str[1] = '\0';
	data->len = 1;
	return (data);
}

t_data	*conversion_string(va_list list)
{
	t_data	*data;
	char	*s;

	data = new_data();
	s = va_arg(list, char *);
	if (!s)
	{
		data->is_null = 1;
		s = ft_strdup("(null)");
	}
	data->str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!data->str)
	{
		if (data->is_null)
			free(s);
		free(data);
		return (NULL);
	}
	ft_strlcpy(data->str, s, ft_strlen(s) + 1);
	data->len = ft_strlen(data->str);
	if (data->is_null)
		free(s);
	return (data);
}
