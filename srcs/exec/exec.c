/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:20:26 by alex              #+#    #+#             */
/*   Updated: 2026/02/03 02:09:55 by amoderan         ###   ########.fr       */
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