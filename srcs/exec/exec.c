/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:39:46 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:39:48 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_special_cmd(t_node *ast, t_exec_data *data)
{
	if (!ft_strncmp(ast->av[0], ":", 2) || !ft_strncmp(ast->av[0], "!", 2))
	{
		data->status = 0;
		return (1);
	}
	if (ast->av[0][0] == '\0')
	{
		data->status = 127;
		ft_putendl_fd("minishell : command not found", 2);
		return (1);
	}
	return (0);
}

int	handle_cmd_validation(t_node *ast, t_exec_data *data)
{
	if (ast->type == NODE_CMD && ast->av && ast->av[0])
	{
		if (check_special_cmd(ast, data))
			return (1);
	}
	if (ast->type == NODE_CMD && (!ast->av || !ast->av[0]))
	{
		data->status = 127;
		ft_putendl_fd("minishell : command not found", 2);
		return (1);
	}
	if (ast->type == NODE_CMD && ast->av && ast->av[0]
		&& builtin_parent(ast->av[0]))
	{
		exec_built_in(ast->av[0], data, ast);
		return (1);
	}
	return (0);
}

void	exec_in_child(t_node *ast, t_exec_data *data)
{
	set_signal_actions_fork();
	data->is_fork = 1;
	if (ast->type == NODE_REDIR)
		exec_redirection(ast, data);
	else if (ast->type == NODE_CMD)
		exec_cmd(ast, data);
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
	exit(data->status);
}

void	handle_exec_status(int status, t_exec_data *data)
{
	if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
	else
		data->status = WEXITSTATUS(status);
}

void	exec_redir_and_cmd(t_node *ast, t_exec_data *data)
{
	pid_t	pid;
	int		status;

	if (handle_cmd_validation(ast, data))
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		data->status = 1;
		return ;
	}
	if (pid == 0)
		exec_in_child(ast, data);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	clear_all_heredocs(data);
	waitpid(pid, &status, 0);
	handle_exec_status(status, data);
	set_signal_actions();
}
