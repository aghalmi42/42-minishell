/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:35:41 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:35:53 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_heredoc_child(char *redir_file, int pipe_fd[2], t_exec_data *data,
		t_node *node)
{
	(void) node;
	set_signal_actions_default();
	close(pipe_fd[0]);
	loop_here_doc(redir_file, pipe_fd[1], data);
	close(pipe_fd[1]);
	data->status = 0;
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
	exit(0);
}

/* On parcours l'ast pour savoir quel noeud est un here_doc */
int	search_here_doc_to_execute(t_node *ast, t_exec_data *data, int *i)
{
	if (!ast)
		return (0);
	if (search_here_doc_to_execute(ast->left, data, i) == -1)
		return (-1);
	if (ast->type == NODE_REDIR && ast->redir_type == TOKEN_HEREDOC)
	{
		if (create_here_doc_file(ast->redir_file, data, (*i)++) == -1)
			return (-1);
	}
	return (search_here_doc_to_execute(ast->right, data, i));
}

void	clear_all_heredocs(t_exec_data *data)
{
	t_here_doc_fd	*curr;

	curr = data->head;
	while (curr)
	{
		if (curr->fd_read > 2)
			close(curr->fd_read);
		if (curr->file_name)
			unlink(curr->file_name);
		curr = curr->next;
	}
	data->head = NULL;
}

void	exec_heredoc_child(char *name, char *limiter, t_exec_data *data)
{
	int	fd;

	set_signal_actions_here_doc();
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		clear_all_heredocs(data);
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
		exit(1);
	}
	loop_here_doc(limiter, fd, data);
	clear_all_heredocs(data);
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
	exit(0);
}

int	create_here_doc_file(char *limiter, t_exec_data *data, int index)
{
	char	*name;
	int		fd;
	pid_t	pid;

	name = gc_strjoin("/tmp/.ms_hd_",
			gc_itoa(index, &data->gc_head_cmd), &data->gc_head_cmd);
	if (!name)
		return (-1);
	pid = fork();
	if (pid == 0)
		exec_heredoc_child(name, limiter, data);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &data->status, 0);
	set_signal_actions();
	if (WIFEXITED(data->status) && WEXITSTATUS(data->status) == 130)
	{
		data->status = 130;
		return (-1);
	}
	fd = open(name, O_RDONLY);
	return (add_here_doc_fd(&data->head, fd, name, &data->gc_head_cmd));
}
