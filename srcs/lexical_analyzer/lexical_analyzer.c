/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:39:34 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/11 15:32:20 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on va extraire un mot et cree un token */
void	extract_word(char *line, int *i, t_token **up)
{
	int		start;
	char	*word;
	t_token	*token;

	start = *i;
	while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\0'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		(*i)++;
	word = ft_substr(line, start, *i - start);
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
