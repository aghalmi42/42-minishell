/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:35:37 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:08 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*manag_width(char *str, t_flags *flag)
{
	char	fill;

	fill = ' ';
	if ((flag->width <= (int)ft_strlen(str)))
		return (str);
	if (flag->zero)
		fill = '0';
	if (flag->minus)
		return (manag_width_left(str, flag->width - ft_strlen(str), fill));
	return (manag_width_right(str, flag->width - ft_strlen(str), fill));
}

char	*manag_width_left(char *str, int nb_fill, char fill)
{
	char	*res;
	int		len;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1 + nb_fill));
	if (!res)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(res, str, len + 1);
	ft_memset(res + len, fill, nb_fill);
	res[len + nb_fill] = '\0';
	free(str);
	return (res);
}

char	*manag_width_right(char *str, int nb_fill, char fill)
{
	char	*res;
	int		len;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1 + nb_fill));
	if (!res)
	{
		free(str);
		return (NULL);
	}
	ft_memset(res, fill, nb_fill);
	ft_strlcpy(res + nb_fill, str, len + 1);
	free(str);
	return (res);
}
