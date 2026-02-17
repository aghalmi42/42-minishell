
#include "../../include/minishell.h"

int	original_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	count_split_word(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

char	*extract_next_word(char *str, int *pos, t_list **gc_head)
{
	int		start;
	int		len;
	char	*word;

	while (str[*pos] && (str[*pos] == ' ' || str[*pos] == '\t' || str[*pos] == '\n'))
		(*pos)++;
	if (!str[*pos])
		return (NULL);
	start = *pos;
	while (str[*pos] && str[*pos] != ' ' && str[*pos] != '\t' && str[*pos] != '\n')
		(*pos)++;
	len = *pos - start;
	word = gc_malloc(len + 1, gc_head);
	if (!word)
		return (NULL);
	ft_memcpy(word, str + start, len);
	word[len] = '\0';
	return (word);
}

void	add_word_token(t_token **last, char *word, t_list **gc_head)
{
	t_token	*new_tok;

	new_tok = new_token(TOKEN_WORD, word, gc_head);
	if (new_tok)
	{
		new_tok->next = (*last)->next;
		(*last)->next = new_tok;
		*last = new_tok;
	}
	gc_free_one(gc_head, word);//free(word);
}

/* verifie si mot a $ et mettre variable remplacer et supp quote */
void	expand_word(t_token *token, t_exec_data *data)
{
	char	*value;

	if (single_quote(token->value))
	{
		value = remove_quote(token->value, &data->gc_head);
		gc_free_one(&data->gc_head, token->value);//free(token->value);
		token->value = value;
		return ;
	}
	value = expand_value(token->value, data);
	free(token->value);
	token->value = value;
}
