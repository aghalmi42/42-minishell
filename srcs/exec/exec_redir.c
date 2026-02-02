/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:16:12 by alex              #+#    #+#             */
/*   Updated: 2026/02/02 06:59:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_redirection(t_node *node, t_exec_data *data)
{
	int	fd;

	if (node->redir_type == TOKEN_HEREDOC)
	{
		fd = data->head->fd_read; 
		t_here_doc_fd *tmp = data->head;
		data->head = data->head->next;
		free(tmp);
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