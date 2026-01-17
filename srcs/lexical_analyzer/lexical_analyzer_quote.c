
#include "../../include/minishell.h"

/* on gere les single quote */
void	manage_quote(char *line, int *i, char *word, int *j)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		word[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	if (line[*i] == '\'')
		(*i)++;
}

/* on gere les double quote */
void	manage_double_quote(char *line, int *i, char *word, int *j)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		word[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	if (line[*i] == '"')
		(*i)++;
}

/* on verifie si le char est un delimiter */
int	delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\0' || c == '|' || c == '<'
		|| c == '>');
}
