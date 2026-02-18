/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 05:34:52 by alex              #+#    #+#             */
/*   Updated: 2026/02/18 02:54:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*gc_malloc(size_t size, t_list **head)
{
	void	*ptr;
	t_list	*new_gb;

	ptr = malloc(size);
	if (!ptr)
		return (gc_delete(head), NULL);
	new_gb = gc_lstnew(ptr);
	if (!new_gb)
		return (free(ptr), gc_delete(head), NULL);
	ft_lstadd_back(head, new_gb);
	return (ptr);
}

void	gc_delete(t_list	**head)
{
	t_list	*next;
	t_list	*curr;

	curr = *head;
	while (curr)
	{
		next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
	*head = NULL;
}

void	gc_free_one(t_list **head, void *ptr)
{
	t_list	*curr;
	t_list	*prev;

	if (!head || !*head || !ptr)
		return ;
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->content == ptr)
		{
			if (prev == NULL)
				*head = curr->next;
			else
				prev->next = curr->next;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}


void	gc_add_back(t_list **gc_head, void *ptr)
{
	t_list	*new_node;
	t_list	*last;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(ptr);
		return ;
	}
	new_node->content = ptr;
	new_node->next = NULL;
	if (!*gc_head)
	{
		*gc_head = new_node;
		return ;
	}
	last = *gc_head;
	while (last->next)
		last = last->next;
	last->next = new_node;
}