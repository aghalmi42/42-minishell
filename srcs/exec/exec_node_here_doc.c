/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 06:21:04 by alex              #+#    #+#             */
/*   Updated: 2026/01/29 06:34:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_here_doc_fd(t_here_doc_fd **head, int fd)
{
	t_here_doc_fd	*last;
	t_here_doc_fd	*new;

	new = here_doc_new(fd);
	if(!new)
		return (-1);
	if (*head == NULL)
		*head = new;
	else
	{
		last = ft_lstlast(*head);
		last->next = new;
	}
	return (0);
}

t_here_doc_fd	*here_doc_last(t_list *here_doc)
{
	if (here_doc == NULL)
		return (NULL);
	while (here_doc->next != NULL)
		here_doc = here_doc->next;
	return (here_doc);
}

t_here_doc_fd	*here_doc_new(int	content)
{
	t_list	*new;

	new = malloc(sizeof(t_here_doc_fd));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}