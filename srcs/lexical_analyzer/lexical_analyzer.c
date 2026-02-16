
#include "../../include/minishell.h"

/* on construit le mot char par char */
int	construct_word(char *line, int *i, char *word, int *j)
{
	int	result;

	while (line[*i] && !delimiter(line[*i]))
	{
		if (line[*i] == '\'')
		{
			result = manage_quote(line, i, word, j);
			if (result == -1)
				return (-1);
		}
		else if (line[*i] == '"')
		{
			result = manage_double_quote(line, i, word, j);
			if (result == -1)
				return (-1);
		}
		else
		{
			word[*j] = line[*i];
			(*i)++;
			(*j)++;
		}
	}
	return (0);
}

/* extrait un  mot en gerant les quote et cree un token */
int	extract_word(char *line, int *i, t_token **up)
{
	int		j;
	int		result;
	char	*word;
	t_token	*token;

	j = 0;
	word = malloc(1000);
	if (!word)
		return (-1);
	result = construct_word(line, i, word, &j);
	if (result == -1)
	{
		free(word);
		return (-1);
	}
	word[j] = '\0';
	token = new_token(TOKEN_WORD, word);
	add_token(up, token);
	free(word);
	return (0);
}

int	process_token(char *line, int *i, t_token **up)
{
	if (manage_parenthese(line, i, up))
		return (1);
	if (manage_logical(line, i, up))
		return (1);
	if (manage_pipe(line, i, up))
		return (1);
	if (manage_redirection(line, i, up))
		return (1);
	if (extract_word(line, i, up) == -1)
		return (-1);
	return (0);
}

/* fonction principal celle qui va tt orchestrer */
t_token	*lexical_analyzer(char *line)
{
	t_token	*up;
	int		i;
	int		result;

	up = NULL;
	i = 0;
	while (line[i])
	{
		skip_all_space(line, &i);
		if (line[i] == '\0')
			break ;
		result = process_token(line, &i, &up);
		if (result == -1)
		{
			free_token(up);
			return (NULL);
		}
	}
	return (up);
}
