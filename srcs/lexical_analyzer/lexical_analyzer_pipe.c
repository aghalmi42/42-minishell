/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:00:26 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:00:28 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on gere la pipe */
int	manage_pipe(char *line, int *i, t_token **up, t_list **gc_head)
{
	t_token	*token;

	if (line[*i] == '|')
	{
		token = new_token(TOKEN_PIPE, NULL, gc_head);
		if (!token)
			return (-1);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	return (0);
}
