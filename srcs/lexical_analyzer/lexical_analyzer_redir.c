/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:01:36 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:01:41 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on gere les heredoc et input redir */
int	manage_input_redirection(char *line, int *i, t_token **up, t_list **gc_head)
{
	t_token	*token;

	if (line[*i] != '<')
		return (0);
	if (line[*i + 1] == '<')
	{
		token = new_token(TOKEN_HEREDOC, NULL, gc_head);
		if (!token)
			return (-1);
		(*i) += 2;
	}
	else
	{
		token = new_token(TOKEN_REDIR_IN, NULL, gc_head);
		if (!token)
			return (-1);
		(*i)++;
	}
	add_token(up, token);
	return (1);
}

/* on gere les append et output redir */
int	manage_output_redirection(char *line, int *i, t_token **up,
			t_list **gc_head)
{
	t_token	*token;

	if (line[*i] != '>')
		return (0);
	if (line[*i + 1] == '>')
	{
		token = new_token(TOKEN_APPEND, NULL, gc_head);
		if (!token)
			return (-1);
		(*i) += 2;
	}
	else
	{
		token = new_token(TOKEN_REDIR_OUT, NULL, gc_head);
		if (!token)
			return (-1);
		(*i)++;
	}
	add_token(up, token);
	return (1);
}

/* orchestre toute les redirection */
int	manage_redirection(char *line, int *i, t_token **up, t_list **gc_head)
{
	if (manage_input_redirection(line, i, up, gc_head))
		return (1);
	if (manage_output_redirection(line, i, up, gc_head))
		return (1);
	return (0);
}
