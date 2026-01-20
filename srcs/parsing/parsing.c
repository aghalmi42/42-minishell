
#include "../../include/minishell.h"

/* split la lst de token au bon endroit */
t_token	*split_token(t_token *token, t_token *split)
{
	t_token	*current;

	if (!token || !split)
		return (NULL);
	current = token;
	while (current && current->next != split)
		current = current->next;
	if (current)
		current->next = NULL;
	return (split->next);
}

/* parsing juste pour une cmd simple --> des token word */
t_node	*parsing_cmd(t_token *token)
{
	t_node	*node;

	node = new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->av = token_tab_av(token);
	return (node);
}

/* parsing pour pipe */
t_node	*parsing_pipe(t_token *token, t_token *pipe_token)
{
	t_node	*node;
	t_token	*right_token;

	node = new_node(NODE_PIPE);
	if (!node)
		return (NULL);
	right_token = split_token(token, pipe_token);
	node->left = parsing(token);
	node->right = parsing(right_token);
	return (node);
}

/* parsing pour redir */
t_node	*parsing_redir(t_token *token, t_token *redir_token)
{
	t_node	*node;
	t_token	*right_token;

	node = new_node(NODE_REDIR);
	if (!node)
		return (NULL);
	node->redir_type = redir_token->type;
	right_token = split_token(token, redir_token);
	if (right_token && right_token->type == TOKEN_WORD)
		node->redir_file = ft_strdup(right_token->value);
	node->left = parsing(token);
	return (node);
}

/* parsing */
t_node	*parsing(t_token *token)
{
	t_token	*pipe_token;
	t_token	*redir_token;

	if (!token)
		return (NULL);
	if (check_pipe_syntax(token) == -1)
		return (NULL);
	if (check_redir_syntax(token) == -1)
		return (NULL);
	pipe_token = search_pipe(token);
	if (pipe_token)
		return (parsing_pipe(token, pipe_token));
	redir_token = search_redir(token);
	if (redir_token)
		return (parsing_redir(token, redir_token));
	return (parsing_cmd(token));
}
