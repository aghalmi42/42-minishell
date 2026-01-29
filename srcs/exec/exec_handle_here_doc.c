/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 05:07:58 by alex              #+#    #+#             */
/*   Updated: 2026/01/29 06:59:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* On parcours l'ast pour savoir quel noeud est un here_doc */
int	search_here_doc_to_execute(t_node *ast, t_exec_data *data)
{
	if (!ast)
		return (0);
	if (search_here_doc_to_execute(ast->left, data) == -1)
		return (-1);
	if (ast->type == NODE_REDIR && ast->redir_type == TOKEN_HEREDOC)
	{
		if (create_here_doc_to_execute(ast->redir_file, data) == -1)
			return (-1);
	}
	return (search_here_doc_to_execute(ast->right, data));
}

/* ici on créé le pipe qui va pouvoir être retrouver plus tard lorsque l'exec des commandes sera fait */
int	create_here_doc_to_execute(t_node *ast, t_exec_data *data)
{
	int	pipe_fd[2];
	pid_t	pid;

	if(pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(pipe_fd[1]), close(pipe_fd[0]), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		loop_here_doc(ast->redir_file, pipe_fd[1]);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	wait_pid(pid, &data->status, 0);
	if (WIFSIGNALED(data->status))
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (add_here_doc_fd(&data->head, pipe_fd[0]));
}

/* fonction pour lire chaque ligne du here_doc jusqu'à avoir le limiter */
void	loop_here_doc(char	*limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

