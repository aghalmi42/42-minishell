
#include "../../include/minishell.h"

/* pour trv la 1er pipe dans la lst de token */
t_token	*search_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/* pour trv la 1er redirection dans la lst de token */
t_token	*search_redir(t_token *token)
{
	t_token *last_redir;

	last_redir = NULL;
	while (token)
	{
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
			last_redir = token;
		token = token->next;
	}
	return (last_redir);
}

/* parsing juste pour une cmd simple --> des token word */
t_node	*parsing_cmd(t_token *token, t_list **gc_head_cmd)
{
	t_node	*node;

	node = new_node(NODE_CMD, gc_head_cmd);
	if (!node)
		return (NULL);
	node->av = token_tab_av(token, gc_head_cmd);
	if (!node->av)
		return (NULL);
	//gc_free_one(gc_head_cmd, token);//free_token(token);
	return (node);
}

/* parsing pour pipe */
t_node	*parsing_pipe(t_token *token, t_token *pipe_token, t_exec_data *data)
{
	t_node	*node;
	t_token	*right_token;

	node = new_node(NODE_PIPE, &data->gc_head_cmd);
	if (!node)
		return (NULL);
	right_token = split_token(token, pipe_token);
	node->left = parsing_pipe_prio(token, data);
	if (!node->left)
		return (NULL);
	node->right = parsing_pipe_prio(right_token, data);
	if (!node->right)
		return (NULL);
	return (node);
}

void	process_redir_file(t_node *node, t_token *right_token, t_token **file, t_list **gc_head_cmd)
{
	if (right_token && right_token->type == TOKEN_WORD)
	{
		node->redir_file = gc_strdup(right_token->value, gc_head_cmd);
		*file = right_token->next;
		// gc_free_one(gc_head_cmd, right_token->value);//free(right_token->value);
		// gc_free_one(gc_head_cmd, right_token->value);free(right_token);
	}
	else
		*file = right_token;
}
