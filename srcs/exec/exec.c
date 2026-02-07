/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:20:26 by alex              #+#    #+#             */
/*   Updated: 2026/02/06 05:52:35 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_main(t_node *ast, t_exec_data *data)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE)
		exec_pipe(ast, data);
	else if (ast->type == NODE_REDIR)
		exec_redirection(ast, data);
	else if (ast->type == NODE_CMD)
		exec_cmd(ast, data);
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