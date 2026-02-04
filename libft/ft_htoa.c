/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:19:01 by alex              #+#    #+#             */
/*   Updated: 2026/02/04 05:40:47 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sh(char *s, int size, unsigned int n)
{
	s[size] = '\0';
	if (n == 0)
		s[0] = '0';
	else
	{
		while (n)
		{
			if (n % 16 < 10)
				s[size - 1] = (n % 16) + '0';
			else
				s[size - 1] = 'A' + (n % 16 - 10);
			n /= 16;
			size--;
		}
	}
}

char	*ft_htoa(unsigned int n)
{
	char			*s;
	unsigned int	nb;
	int				size;

	size = 0;
	nb = n;
	if (n == 0)
		size++;
	while (nb)
	{
		size++;
		nb /= 16;
	}
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	ft_sh(s, size, n);
	return (s);
}
