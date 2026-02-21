/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:58:13 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:58:13 by aghalmi          ###   ########.fr       */
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
