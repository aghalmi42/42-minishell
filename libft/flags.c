/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:51:06 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:52 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_flags	*new_flag(void)
{
	t_flags	*flag;

	flag = malloc(sizeof(t_flags));
	if (!flag)
		return (NULL);
	flag->zero = 0;
	flag->dot = 0;
	flag->hashtag = 0;
	flag->space = 0;
	flag->plus = 0;
	flag->minus = 0;
	flag->width = 0;
	flag->precision = 0;
	return (flag);
}

void	priority_flags(t_flags *flag)
{
	if (flag->zero && flag->minus)
		flag->zero = 0;
	if (flag->zero && flag->dot)
		flag->zero = 0;
	if (flag->plus && flag->space)
		flag->space = 0;
	if (flag->minus && !flag->width)
		flag->minus = 0;
}
