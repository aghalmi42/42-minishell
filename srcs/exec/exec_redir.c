/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:16:12 by alex              #+#    #+#             */
/*   Updated: 2026/02/07 05:47:05 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_redirection(t_node *node, t_exec_data *data)
{
	int				fd;
	t_here_doc_fd	*tmp;

	if (node->redir_type == TOKEN_HEREDOC)
	{
		fd = data->head->fd_read; 
		tmp = data->head;
		free(tmp);
		data->head = data->head->next;
	}
	else
		fd = open_redir_file(node); 
	if (fd == -1)
		exit(1);
	if (node->redir_type == TOKEN_REDIR_IN || node->redir_type == TOKEN_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_main(node->left, data);
}

int	open_redir_file(t_node *node)
{
	int	fd;

	if (node->redir_type == TOKEN_REDIR_IN)
		fd = open(node->redir_file, O_RDONLY);
	else if (node->redir_type == TOKEN_REDIR_OUT)
		fd = open(node->redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->redir_type == TOKEN_APPEND)
		fd = open(node->redir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);

	if (fd == -1)
	{
		perror(node->redir_file);
		return (-1);
	}
	return (fd);
}