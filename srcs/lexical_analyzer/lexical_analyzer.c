/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:39:34 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/10 11:53:19 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* on va decouper notre ligne en espace et cree des TOKENWORD pour chaque mot */
t_token	*lexical_analyzer(char *line)
{
	t_token	*up;
	t_token	*token;
	int		i;
	int		start;
	char	*word;

	up = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			break ;
		start = i;
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			i++;
		word = ft_substr(line, start, i - start);
		token = new_token(TOKEN_WORD, word);
		add_token(&up, token);
		free(word);
	}
	return (up);
}
