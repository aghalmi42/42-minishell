/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:39:34 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/17 17:06:44 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on construit le mot char par char */
void	construct_word(char *line, int *i, char *word, int *j)
{
	while (line[*i] && !delimiter(line[*i]))
	{
		if (line[*i] == '\'')
			manage_quote(line, i, word, j);
		else if (line[*i] == '"')
			manage_double_quote(line, i, word, j);
		else
		{
			word[*j] = line[*i];
			(*i)++;
			(*j)++;
		}
	}
}

/* extrait un  mot en gerant les quote et cree un token */
void	extract_word(char *line, int *i, t_token **up)
{
	int		j;
	char	*word;
	t_token	*token;

	j = 0;
	word = malloc(1000);
	if (!word)
		return ;
	construct_word(line, i, word, &j);
	word[j] = '\0';
	token = new_token(TOKEN_WORD, word);
	add_token(up, token);
	free(word);
}

/* fonction principal celle qui va tt orchestrer */
t_token	*lexical_analyzer(char *line)
{
	t_token	*up;
	int		i;

	up = NULL;
	i = 0;
	while (line[i])
	{
		skip_all_space(line, &i);
		if (line[i] == '\0')
			break ;
		if (manage_pipe(line, &i, &up))
			continue ;
		if (manage_redirection(line, &i, &up))
			continue ;
		extract_word(line, &i, &up);
	}
	return (up);
}
