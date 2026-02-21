/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:36:12 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:41:36 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* listes chaines des fd des here, marche commes les ft_lst */
int	add_here_doc_fd(t_here_doc_fd **head, int fd, char *name,
			t_list **gc_head_cmd)
{
	t_here_doc_fd	*last;
	t_here_doc_fd	*new;

	new = here_doc_new(fd, gc_head_cmd, name);
	if (!new)
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
t_here_doc_fd	*here_doc_new(int content, t_list **gc_head_cmd, char *name)
{
	t_here_doc_fd	*new;

	new = gc_malloc(sizeof(t_here_doc_fd), gc_head_cmd);
	if (!new)
		return (NULL);
	new->fd_read = content;
	new->next = NULL;
	new->file_name = name;
	return (new);
}

/* libere tt les lst de herdoc */
void	free_here_doc_list(t_here_doc_fd *head)
{
	t_here_doc_fd	*tmp;

	while (head)
	{
		tmp = head->next;
		close(head->fd_read);
		free(head);
		head = tmp;
	}
}
