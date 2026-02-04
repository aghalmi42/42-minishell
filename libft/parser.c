/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:04:27 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:01 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	check_flags(char c, t_flags *flag)
{
	if (c == '0')
		flag->zero = 1;
	if (c == '-')
		flag->minus = 1;
	if (c == '+')
		flag->plus = 1;
	if (c == ' ')
		flag->space = 1;
	if (c == '#')
		flag->hashtag = 1;
	return (c == '0' || c == '-'
		|| c == '+' || c == ' ' || c == '#');
}

void	parse_flag(t_flags *flag, char const *str, int *j, va_list list)
{
	(*j)++;
	while (str[*j] && check_flags(str[*j], flag))
		(*j)++;
	parse_width(flag, str, j, list);
	if (str[*j] == '.')
	{
		flag->dot = 1;
		parse_precision(flag, str, j, list);
	}
	priority_flags(flag);
}

void	parse_width(t_flags *flag, char const *str, int *j, va_list list)
{
	if (str[*j] == '*')
	{
		flag->width = (int)(va_arg(list, int));
		if (flag->width < 0)
		{
			flag->minus = 1;
			flag->width = -flag->width;
		}
		(*j)++;
	}
	else
	{
		while (str[*j] && ft_isdigit(str[*j]))
		{
			flag->width = flag->width * 10 + (str[*j] - '0');
			(*j)++;
		}
	}
}

void	parse_precision(t_flags *flag, char const *str, int *j, va_list list)
{
	(*j)++;
	if (str[*j] == '*')
	{
		flag->precision = (int)(va_arg(list, int));
		if (flag->precision < 0)
			flag->dot = 0;
		(*j)++;
	}
	else
	{
		while (str[*j] && ft_isdigit(str[*j]))
		{
			flag->precision = flag->precision * 10 + (str[*j] - '0');
			(*j)++;
		}
	}
}
