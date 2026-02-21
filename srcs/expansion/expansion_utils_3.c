/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:44:15 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:44:15 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_words(t_token *current, char *expand, int word_count,
			t_list **gc_head_cmd)
{
	t_token	*last;
	char	*word;
	int		pos;
	int		i;

	pos = 0;
	i = 0;
	last = current;
	while (i < word_count)
	{
		word = extract_next_word(expand, &pos, gc_head_cmd);
		if (!word)
			break ;
		if (i == 0)
		{
			gc_free_one(gc_head_cmd, current->value);
			current->value = word;
		}
		else
			add_word_token(&last, word, gc_head_cmd);
		i++;
	}
}

void	insert_split_token(t_token *current, char *expand, t_list **gc_head_cmd)
{
	int	word_count;

	word_count = count_split_word(expand);
	if (word_count == 0)
	{
		gc_free_one(gc_head_cmd, current->value);
		current->value = gc_strdup("", gc_head_cmd);
		return ;
	}
	process_words(current, expand, word_count, gc_head_cmd);
}

int	dollar_special(char *str, int *i)
{
	if (ft_isdigit(str[*i + 1]))
	{
		(*i) += 2;
		return (1);
	}
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	handle_quotes(char *str, int *var)
{
	if (str[var[0]] == '\'' && var[2] == 0)
	{
		var[2] = 1;
		var[0]++;
	}
	else if (str[var[0]] == '\'' && var[2] == 1)
	{
		var[2] = 0;
		var[0]++;
	}
	else if (str[var[0]] == '"' && var[2] == 0)
	{
		var[2] = 2;
		var[0]++;
	}
	else if (str[var[0]] == '"' && var[2] == 2)
	{
		var[2] = 0;
		var[0]++;
	}
}

void	case_expand(char *str, char *result, int *var, t_exec_data *data)
{
	while (str[var[0]])
	{
		if ((str[var[0]] == '\'' && var[2] != 2)
			|| (str[var[0]] == '"' && var[2] != 1))
			handle_quotes(str, var);
		else if (to_expand(str, var[0], var[2]))
			var[1] += manage_variable(str, &var[0], result + var[1],
					data);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '?')
			var[1] += manage_exit_code(&var[0], result + var[1], data);
		else if (str[var[0]] == '$' && str[var[0] + 1] == '$')
			var[1] += manage_pid(&var[0], result + var[1], &data->gc_head_cmd);
		else if (str[var[0]] == '$' && var[2] != 1)
		{
			if (dollar_special(str, &var[0]))
				continue ;
			copy_char(str, &var[0], result, &var[1]);
		}
		else
			copy_char(str, &var[0], result, &var[1]);
	}
}
