/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:39:45 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/10 11:51:28 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* ici jai cree un token quon va stocker en allouant de la memoire */
t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value != NULL)
		token->value = ft_strdup(value);
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

/* pour voir si nos token sont bien cree grace au lexical analyzer
fonction quon doit clean a la fin !!!!!1 */

void	print_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		printf("type : %d ||| value %s\n", current->type, current->value);
		current = current->next;
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
