
#include "../../include/minishell.h"

/* split la lst de token au bon endroit */
t_token	*split_token(t_token *token, t_token *split)
{
	t_token	*current;
	t_token *next;

	if (!token || !split)
		return (NULL);
	current = token;
	while (current && current->next != split)
		current = current->next;
	if (current)
		current->next = NULL;
	next = split->next;
	if (split->value)
		free(split->value);
	free(split);
	return (next);
}

/* parsing juste pour une cmd simple --> des token word */
t_node	*parsing_cmd(t_token *token)
{
	t_node	*node;

	node = new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->av = token_tab_av(token);
	free_token(token);
	return (node);
}

/* parsing pour pipe */
t_node	*parsing_pipe(t_token *token, t_token *pipe_token, t_exec_data *data)
{
	t_node	*node;
	t_token	*right_token;

	node = new_node(NODE_PIPE);
	if (!node)
		return (NULL);
	right_token = split_token(token, pipe_token);
	node->left = parsing_pipe_prio(token, data);
	node->right = parsing_pipe_prio(right_token, data);
	// free_token(token);
	// free_token(right_token);
	return (node);
}

/* parsing pour redir */
t_node	*parsing_redir(t_token *token, t_token *redir_token, t_exec_data *data)
{
	t_node	*node;
	t_token	*right_token;
	t_token *file;

	if (token == redir_token)
		return (NULL);
	node = new_node(NODE_REDIR);
	if (!node)
		return (NULL);
	node->redir_type = redir_token->type;
	right_token = split_token(token, redir_token);
	if (right_token && right_token->type == TOKEN_WORD)
	{
		node->redir_file = ft_strdup(right_token->value);
		file = right_token->next;
		free(right_token->value);
		free(right_token);
	}
	else 
		file = right_token;
	if (file)
		node->left = parsing(file, data);
	else
		node->left = parsing(token, data);
	// if (token && token != redir_token)
	// free_token(token);
	//free_token(file);
	return (node);
}

/* parsing */
t_node	*parsing(t_token *token, t_exec_data *data)
{
	t_token	*logical_token;

	if (!token)
		return (NULL);
	if (check_syntax(token, data) == -1)
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
