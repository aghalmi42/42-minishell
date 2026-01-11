/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:12:19 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/11 15:40:48 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on saute les espace et les tab */
void	skip_all_space(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

/* on gere la pipe */
int	manage_pipe(char *line, int *i, t_token **up)
{
	t_token	*token;

	if (line[*i] == '|')
	{
		token = new_token(TOKEN_PIPE, NULL);
		add_token(up, token);
		(*i)++;
		return (1);
	}
	return (0);
}

/* on gere les heredoc et input redir */
int	manage_input_redirection(char *line, int *i, t_token **up)
{
	t_token	*token;

	if (line[*i] != '<')
		return (0);
	if (line[*i + 1] == '<')
	{
		token = new_token(TOKEN_HEREDOC, NULL);
		(*i) += 2;
	}
	else
	{
		token = new_token(TOKEN_REDIR_IN, NULL);
		(*i)++;
	}
	add_token(up, token);
	return (1);
}

/* on gere les append et output redir */
int	manage_output_redirection(char *line, int *i, t_token **up)
{
	t_token	*token;

	if (line[*i] != '>')
		return (0);
	if (line[*i + 1] == '>')
	{
		token = new_token(TOKEN_APPEND, NULL);
		(*i) += 2;
	}
	else
	{
		token = new_token(TOKEN_REDIR_OUT, NULL);
		(*i)++;
	}
	add_token(up, token);
	return (1);
}

/* orchestre toute les redirection */
int	manage_redirection(char *line, int *i, t_token **up)
{
	if (manage_input_redirection(line, i, up))
		return (1);
	if (manage_output_redirection(line, i, up))
		return (1);
	return (0);
}
