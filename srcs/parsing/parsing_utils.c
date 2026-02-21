/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:09:01 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:09:15 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* pour cree un nv noeud */
t_node	*new_node(t_node_type type, t_list **gc_head_cmd)
{
	t_node	*node;

	node = gc_malloc(sizeof(t_node), gc_head_cmd);
	if (!node)
		return (NULL);
	node->type = type;
	node->av = NULL;
	node->redir_type = 0;
	node->redir_file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* free notre en recursive */
void	free_ast(t_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->av)
	{
		i = 0;
		while (node->av[i])
		{
			free(node->av[i]);
			i++;
		}
		free(node->av);
	}
	if (node->redir_file)
		free(node->redir_file);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

/* count le nmbr de av */
int	count_av(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == TOKEN_WORD)
	{
		if (token->value && token->value[0] != '\0')
			count++;
		token = token->next;
	}
	return (count);
}

/* convert token en tableau de av */
char	**token_tab_av(t_token *token, t_list **gc_head_cmd)
{
	char	**av;
	int		i;
	int		count;

	i = 0;
	count = count_av(token);
	av = gc_malloc(sizeof(char *) * (count + 1), gc_head_cmd);
	if (!av)
		return (NULL);
	while (token && token->type == TOKEN_WORD)
	{
		if (token->value && token->value[0] != '\0')
		{
			av[i] = gc_strdup(token->value, gc_head_cmd);
			if (!av[i])
				return (NULL);
			i++;
		}
		token = token->next;
	}
	av[i] = NULL;
	return (av);
}

/* split la lst de token au bon endroit */
t_token	*split_token(t_token *token, t_token *split)
{
	t_token	*current;
	t_token	*next;

	if (!token || !split)
		return (NULL);
	current = token;
	while (current && current->next != split)
		current = current->next;
	if (current)
		current->next = NULL;
	next = split->next;
	return (next);
}
