
#include "../../include/minishell.h"

/* pour cree un nv noeud */
t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
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
char	**token_tab_av(t_token *token)
{
	char	**av;
	int		i;
	int		count;

	i = 0;
	count = count_av(token);
	av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (NULL);
	while (token && token->type == TOKEN_WORD)
	{
		if (token->value && token->value[0] != '\0')
		{
			av[i] = ft_strdup(token->value);
			i++;
		}
		token = token->next;
	}
	av[i] = NULL;
	return (av);
}

/* fonction quon va supp a la fin */
void	print_ast(t_node *node, int tmp)
{
	int	i;
	int	j;

	j = 0;
	if (!node)
		return ;
	while (j < tmp)
	{
		printf("  ");
		j++;
	}
	if (node->type == NODE_CMD)
	{
		printf("CMD : ");
		i = 0;
		while (node->av && node->av[i])
		{
			printf("%s ", node->av[i]);
			i++;
		}
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE\n");
		print_ast(node->left, tmp + 1);
		print_ast(node->right, tmp + 1);
	}
	else if (node->type == NODE_REDIR)
	{
		printf("REDIR %d --> %s\n", node->redir_type, node->redir_file);
		print_ast(node->left, tmp + 1);
	}
	else if (node->type == NODE_AND)
	{
		printf("AND\n");
		print_ast(node->left, tmp + 1);
		print_ast(node->right, tmp + 1);
	}
	else if (node->type == NODE_OR)
	{
		printf("OR\n");
		print_ast(node->left, tmp + 1);
		print_ast(node->right, tmp + 1);
	}
}
