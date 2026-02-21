/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_logical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:59:55 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:59:55 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* gere les && et les || */
int	manage_logical(char *line, int *i, t_token **up, t_list **gc_head)
{
	t_token	*token;

	if (line[*i] == '&' && line[*i + 1] == '&')
	{
		token = new_token(TOKEN_AND, NULL, gc_head);
		if (!token)
			return (-1);
		add_token(up, token);
		(*i) += 2;
		return (1);
	}
	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		token = new_token(TOKEN_OR, NULL, gc_head);
		if (!token)
			return (-1);
		add_token(up, token);
		(*i) += 2;
		return (1);
	}
	return (0);
}
