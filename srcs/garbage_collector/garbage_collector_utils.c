/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:57:58 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:58:10 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* split */
static int	count_words(char const *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && !word)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static int	split_words(char **result, char const *s, char c, t_list **gc_head)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[j] = gc_substr(s, start, i - start, gc_head);
		if (!result[j++])
			return (0);
	}
	result[j] = NULL;
	return (1);
}

char	**gc_split(char const *s, char c, t_list **gc_head)
{
	char	**result;

	if (!s)
		return (NULL);
	result = gc_malloc(sizeof(char *) * (count_words(s, c) + 1), gc_head);
	if (!result)
		return (NULL);
	if (!split_words(result, s, c, gc_head))
		return (NULL);
	return (result);
}

char	*gc_substr(char const *s, unsigned int start, size_t len,
			t_list **gc_head)
{
	size_t	i;
	char	*str;
	size_t	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (gc_strdup("", gc_head));
	if (start + len > s_len)
		len = s_len - start;
	str = gc_malloc(len + 1, gc_head);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
