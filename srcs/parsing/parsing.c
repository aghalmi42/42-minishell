
#include "../../include/minishell.h"

t_node	*create_redir_node(t_token *redir_token, t_token *right_token, t_token *left_token, t_exec_data *data)
{
	t_node	*node;
	t_token	*file;

	node = new_node(NODE_REDIR, &data->gc_head);
	if (!node)
		return (NULL);
	node->redir_type = redir_token->type;
	process_redir_file(node, right_token, &file);
	if (file)
		node->left = parsing_no_check(file, data);
	else if (left_token)
		node->left = parsing_no_check(left_token, data);
	else
		node->left = NULL;
	return (node);
}

t_node	*handle_redir_at_start(t_token *redir_token, t_exec_data *data)
{
	t_token	*right_token;

	right_token = redir_token->next;
	return (create_redir_node(redir_token, right_token, NULL, data));
}

t_node	*parsing_redir(t_token *token, t_token *redir_token, t_exec_data *data)
{
	t_token	*right_token;

	if (token == redir_token)
		return (handle_redir_at_start(redir_token, data));
	right_token = split_token(token, redir_token, &data->gc_head);
	return (create_redir_node(redir_token, right_token, token, data));
}

/* parsing sans verif de syntax */
t_node	*parsing_no_check(t_token *token, t_exec_data *data)
{
	t_token	*logical_token;

	if (!token)
		return (NULL);
	logical_token = search_logical(token);
	if (logical_token)
	{
		if (logical_token->type == TOKEN_AND)
			return (parsing_and(token, logical_token, data));
		else
			return (parsing_or(token, logical_token, data));
	}
	return (parsing_pipe_prio(token, data));
}

/* parsing avec verif de syntax */
t_node	*parsing(t_token *token, t_exec_data *data)
{
	if (!token)
		return (NULL);
	if (check_syntax(token, data) == -1)
		return (NULL);
	return (parsing_no_check(token, data));
}
