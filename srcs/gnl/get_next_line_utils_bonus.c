/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:04:29 by alex              #+#    #+#             */
/*   Updated: 2025/11/26 00:51:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2, char c_one, char c_two)
{
	size_t	i;
	size_t	j;
	size_t	len_one;
	size_t	len_two;
	char	*s;

	i = 0;
	j = 0;
	len_one = ft_strlen_gnl(s1, c_one);
	len_two = ft_strlen_gnl(s2, c_two);
	s = malloc(sizeof(char) * (len_one + len_two + 1));
	if (!s)
		return (NULL);
	while (s1 && i < len_one)
	{
		s[i] = s1[i];
		i++;
	}
	while (s2 && j < len_two)
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

size_t	ft_strlen_gnl(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	is_end_of_line_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
