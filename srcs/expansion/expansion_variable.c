
#include "../../include/minishell.h"

char	*find_env_value(char *var_name, char **env)
{
	int	i;
	int	len;

	i = 0;
	if (!var_name || !env)
		return (NULL);
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

/* extrait user */
char	*extract_var_name(char *str, int *i)
{
	char	*name;
	int		j;
	int		start;

	j = 0;
	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = malloc(*i - start + 1);
	if (!name)
		return (NULL);
	while (start < *i)
	{
		name[j] = str[start];
		j++;
		start++;
	}
	name[j] = '\0';
	return (name);
}

/* copie une string dans result et return le nb de char*/
int	copy_to_result(char *src, char *result)
{
	int	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		result[i] = src[i];
		i++;
	}
	return (i);
}

/* gere lexpansion dune variable $USER et return nb char ajt*/
int	manage_variable(char *str, int *i, char *result, char **env)
{
	char	*var_name;
	char	*var_value;
	int		count;

	var_name = extract_var_name(str, i);
	var_value = find_env_value(var_name, env);
	count = copy_to_result(var_value, result);
	free(var_name);
	return (count);
}

/* gere les quote simple et douvle */
void	manage_exp_quote(char c, int *in_quote, int *i)
{
	if (c == '\'')
		*in_quote = !(*in_quote);
	(*i)++;
}
