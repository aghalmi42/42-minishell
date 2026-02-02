/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 06:21:04 by alex              #+#    #+#             */
/*   Updated: 2026/02/02 07:09:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* listes chaines des fd des here, marche commes les ft_lst */
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
		last = here_doc_last(*head);
		last->next = new;
	}
	return (0);
}

/* retourn le dernier here_doc_fd */
t_here_doc_fd	*here_doc_last(t_here_doc_fd *here_doc)
{
	if (here_doc == NULL)
		return (NULL);
	while (here_doc->next != NULL)
		here_doc = here_doc->next;
	return (here_doc);
}

/* Créé un nouveau here_doc_fd */
t_here_doc_fd	*here_doc_new(int	content)
{
	t_here_doc_fd	*new;

	new = malloc(sizeof(t_here_doc_fd));
	if (!new)
		return (NULL);
	new->fd_read = content;
	new->next = NULL;
	return (new);
}