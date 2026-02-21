/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:41:48 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:41:49 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_redir_fd(t_node *node, t_exec_data *data, t_here_doc_fd **tmp)
{
	int	fd;

	*tmp = NULL;
	if (node->redir_type == TOKEN_HEREDOC)
	{
		if (!data->current_hd)
			return (-1);
		fd = data->current_hd->fd_read;
		*tmp = data->head;
		data->current_hd = data->current_hd->next;
	}
	else
		fd = open_redir_file(node);
	return (fd);
}

void	handle_redir_error(t_node *node, t_exec_data *data, t_here_doc_fd *tmp)
{
	(void) node;
	(void) tmp;
	data->status = 1;
	if (data->is_fork)
	{
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
		exit(1);
	}
}

void	exec_redirection(t_node *node, t_exec_data *data)
{
	int				fd;
	t_here_doc_fd	*tmp;

	fd = get_redir_fd(node, data, &tmp);
	if (fd == -1)
		return (handle_redir_error(node, data, tmp));
	if (node->redir_type == TOKEN_REDIR_IN
		|| node->redir_type == TOKEN_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	if (tmp)
		tmp->fd_read = -1;
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
