/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_parenthese.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:00:18 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:00:18 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* pour gerer les parenthesse */
int	manage_parenthese(char *line, int *i, t_token **up, t_list **gc_head)
{
	t_token	*token;

	if (line[*i] == '(')
	{
		token = new_token(TOKEN_LEFT_PAREN, NULL, gc_head);
		if (!token)
			return (-1);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	else if (line[*i] == ')')
	{
		token = new_token(TOKEN_RIGHT_PAREN, NULL, gc_head);
		if (!token)
			return (-1);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	return (0);
}
