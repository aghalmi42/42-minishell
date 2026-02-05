/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:02:50 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:18 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*manag_prefix(char *str, t_data *data, t_flags *flag, char c)
{
	char	*res;

	res = NULL;
	if (c == 'd' || c == 'i')
		return (manag_prefix_int(str, flag, data));
	else if ((c == 'x' || c == 'X') && !data->is_zero && flag->hashtag)
	{
		return (manag_prefix_hex(str, c));
	}
	else if (c == 'p' && !data->is_null)
	{
		res = ft_strjoin("0x", str);
		free(str);
		return (res);
	}
	else
		return (str);
}

char	*manag_prefix_int(char *str, t_flags *flag, t_data *data)
{
	char	*res;

	if (data->is_neg)
	{
		res = ft_strjoin("-", str);
		free(str);
	}
	else if (flag->plus)
	{
		res = ft_strjoin("+", str);
		free(str);
	}
	else if (flag->space)
	{
		res = ft_strjoin(" ", str);
		free(str);
	}
	else
		res = str;
	return (res);
}

char	*manag_prefix_hex(char *str, char c)
{
	char	*res;

	if (c == 'x')
		res = ft_strjoin("0x", str);
	else
		res = ft_strjoin("0X", str);
	free(str);
	return (res);
}
