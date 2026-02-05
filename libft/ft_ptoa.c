/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:56:25 by amoderan          #+#    #+#             */
/*   Updated: 2026/02/04 05:40:37 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sp(char *s, int size, unsigned long long n)
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
				s[size - 1] = 'a' + (n % 16 - 10);
			n /= 16;
			size--;
		}
	}
}

char	*ft_ptoa(unsigned long long n)
{
	char				*s;
	unsigned long long	nb;
	int					size;

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
	ft_sp(s, size, n);
	return (s);
}
