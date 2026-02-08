/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:20:26 by alex              #+#    #+#             */
/*   Updated: 2026/02/08 13:39:11 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_main(t_node *ast, t_exec_data *data)
{
	if (!ast)
		return ;
	if (ast->type == NODE_AND)
		exec_and(ast, data);
	else if (ast->type == NODE_OR)
		exec_or(ast, data);
	else if (ast->type == NODE_PIPE)
		exec_pipe(ast, data);
	else
		exec_redir_and_cmd(ast, data);
}

int builtin_parent(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("cd", cmd, 3) && cmd[2] == '\0')
		return (1);
	if (!ft_strncmp("export", cmd, 7) && cmd[6] == '\0')
		return (1);
	if (!ft_strncmp("unset", cmd, 6) && cmd[5] == '\0')
		return (1);
	if (!ft_strncmp("exit", cmd, 5) && cmd[4] == '\0')
		return (1);
	return (0);
}

void	exec_redir_and_cmd(t_node *ast, t_exec_data *data)
{
	pid_t	pid;
	int		status;

	if (ast->type == NODE_CMD && ast->av && ast->av[0] && builtin_parent(ast->av[0]))
	{
		exec_built_in(ast->av[0], data, ast);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		data->status = 1;
		return ;
	}
	if (pid == 0)
	{
		set_signal_actions_default();
		data->is_fork = 1;
		if (ast->type == NODE_REDIR)
			exec_redirection(ast, data);
		else if (ast->type == NODE_CMD)
			exec_cmd(ast, data);
		exit(data->status);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
	else
		data->status = WEXITSTATUS(status);
	set_signal_actions();
}

// void	exec_main(t_node *ast, t_exec_data *data)
// {
// 	if (!ast)
// 		return ;
// 	if (ast->type == NODE_PIPE)
// 		exec_pipe(ast, data);
// 	else
// 		exec_other_cmd(ast, data);
// }

// void	exec_other_cmd(t_node *ast, t_exec_data *data)
// {
// 	if (is_a_built_in(ast->av[0]));
// 		exec_built_in(ast, data);
	
// }