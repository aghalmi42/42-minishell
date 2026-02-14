/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:16:12 by alex              #+#    #+#             */
/*   Updated: 2026/02/14 16:27:36 by aghalmi          ###   ########.fr       */
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
		data->head = data->head->next;
		free(tmp);
	}
	else
		fd = open_redir_file(node); 
	if (fd == -1)
	{
		data->status = 1;
		if (data->is_fork)
		{
			free_ast(node);
			free_envp(data);
			if(tmp)
				free(tmp);
			exit(1);
		}
		return ;
	}
	if (node->redir_type == TOKEN_REDIR_IN || node->redir_type == TOKEN_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	if (node->left)
		exec_main(node->left, data);
	else 
		data->status = 0;
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
