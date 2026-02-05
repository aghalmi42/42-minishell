
#include "../../include/minishell.h"

/* detecte si mot est dans une single quote */
int	single_quote(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (1);
	return (0);
}

/* cherche le dollars */
int	dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/* pour supp quote */
char	*remove_quote(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

/* copie un caractere normal */
void	copy_char(char *str, int *i, char *result, int *j)
{
	result[*j] = str[*i];
	(*i)++;
	(*j)++;
}

/*verif si on doit expand le dollars */
int	to_expand(char *str, int i, int in_quote)
{
	if (str[i] != '$' || in_quote)
		return (0);
	if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
		return (1);
	return (0);
}

