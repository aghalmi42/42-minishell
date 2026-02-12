/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 02:56:52 by amoderan          #+#    #+#             */
/*   Updated: 2026/02/12 04:59:22 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*gb_malloc(size_t size, t_list **head)
{
	void	*ptr;
	t_list	*new_gb;

	ptr = malloc(sizeof(size));
	if (!ptr)
		return (gb_delete(head), NULL);
	new_gb = ft_lstnew(ptr);
	if (!new_gb)
		return (gb_delete(head), NULL);
	ft_lstadd_back(head, new_gb);
	return (ptr);
}

void	gb_delete(t_list	**head)
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
