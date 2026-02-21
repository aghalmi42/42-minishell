/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:04:43 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:04:43 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* cherche le premier && ouu || dans la lst de token */
t_token	*search_logical(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_AND || token->type == TOKEN_OR)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/* parsing pouur pipe prioriter haute */
t_node	*parsing_pipe_prio(t_token *token, t_exec_data *data)
{
	t_token	*pipe_token;
	t_token	*redir_token;
	t_token	*paren_token;

	if (!token)
		return (NULL);
	paren_token = search_parenthese(token);
	if (paren_token)
		return (parsing_subshell(token, data));
	pipe_token = search_pipe(token);
	if (pipe_token)
		return (parsing_pipe(token, pipe_token, data));
	redir_token = search_redir(token);
	if (redir_token)
		return (parsing_redir(token, redir_token, data));
	return (parsing_cmd(token, &data->gc_head_cmd));
}

/* parsing pouur les && */
t_node	*parsing_and(t_token *token, t_token *and_token, t_exec_data *data)
{
	t_node	*node;
	t_token	*right_token;

	node = new_node(NODE_AND, &data->gc_head_cmd);
	if (!node)
		return (NULL);
	right_token = split_token(token, and_token);
	node->left = parsing_pipe_prio(token, data);
	node->right = parsing_no_check(right_token, data);
	return (node);
}

/* parsing pouur les || */
t_node	*parsing_or(t_token *token, t_token *or_token, t_exec_data *data)
{
	t_node	*node;
	t_token	*right_token;

	node = new_node(NODE_OR, &data->gc_head_cmd);
	if (!node)
		return (NULL);
	right_token = split_token(token, or_token);
	node->left = parsing_pipe_prio(token, data);
	node->right = parsing_no_check(right_token, data);
	return (node);
}
