/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:01:31 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:01:33 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on gere les single quote */
int	manage_quote(char *line, int *i, char *word, int *j)
{
	word[*j] = line[*i];
	(*j)++;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		word[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	if (line[*i] == '\0')
		return (-1);
	word[*j] = line[*i];
	(*j)++;
	(*i)++;
	return (0);
}

/* on gere les double quote */
int	manage_double_quote(char *line, int *i, char *word, int *j)
{
	word[*j] = line[*i];
	(*j)++;
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		word[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	if (line[*i] == '\0')
		return (-1);
	word[*j] = line[*i];
	(*j)++;
	(*i)++;
	return (0);
}

/* on verifie si le char est un delimiter */
int	delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\0' || c == '|' || c == '<'
		|| c == '>' || c == '(' || c == ')');
}
