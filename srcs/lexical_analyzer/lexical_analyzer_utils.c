
#include "../../include/minishell.h"

/* ici jai cree un token quon va stocker en allouant de la memoire */
t_token	*new_token(t_token_type type, char *value, t_list **gc_head)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), gc_head);
	if (!token)
		return (NULL);
	token->type = type;
	if (value != NULL)
	{
		token->value = gc_strdup(value, gc_head);
		if (!token->value)
			return (NULL);
	}
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

/* jajoute un token a la fin de la liste chainer */
void	add_token(t_token **up, t_token *new)
{
	t_token	*tmp;

	if (*up == NULL)
		*up = new;
	else
	{
		tmp = *up;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/* on va free tt les token et sa valeur */
void	free_token(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current != NULL)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

/* on saute les espace et les tab */
void	skip_all_space(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}
