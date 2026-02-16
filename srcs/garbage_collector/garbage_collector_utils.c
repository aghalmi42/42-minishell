/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 06:34:40 by alex              #+#    #+#             */
/*   Updated: 2026/02/16 08:32:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	gc_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	gc_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

t_list	*gc_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

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


// static void	gb_free_split(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }

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

char	*gc_strdup(const char *s, t_list **gc_head)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = gc_malloc(sizeof(char) * (ft_strlen(s) + 1), gc_head);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*gc_strjoin(char const *s1, char const *s2, t_list **gc_head)
{
	size_t	i;
	size_t	j;
	char	*tabi;

	i = 0;
	j = 0;
	tabi = gc_malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1, gc_head);
	if (!tabi)
		return (NULL);
	while (s1[i])
	{
		tabi[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tabi[i] = s2[j];
		i++;
		j++;
	}
	tabi[i] = '\0';
	return (tabi);
}

char	*gc_substr(char const *s, unsigned int start, size_t len, t_list **gc_head)
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

char	*gc_strtrim(char const *s1, char const *set, t_list **gc_head)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	result = gc_malloc(sizeof(char) * (end - start + 1), gc_head);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 1);
	return (result);
}