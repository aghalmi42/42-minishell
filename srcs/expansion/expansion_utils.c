
#include "../../include/minishell.h"

/* detecte si mot est dans une single quote */
int	single_quote(char *str)
{
	int i;

	i = 1;
	if (!str || str[0] != '\'')
		return (0);
	while(str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'' && str[i + 1] == '\0')
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
	int len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"' && str[len - 1] == '"')))
	{
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		ft_memcpy(result, str + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (ft_strdup(str));
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
	if (str[i] != '$')
		return (0);
	if (in_quote == 1)
		return (0);
	if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
		return (1);
	return (0);
}
