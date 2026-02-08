
#include "../../include/minishell.h"

char	*find_env_value(char *var_name, t_list *envp)
{
	t_list *current;
	t_env	*env;
	int	len;

	if (!var_name || !envp)
		return (NULL);
	len = ft_strlen(var_name);
	current = envp;
	while (current)
	{
		env = current->content;
		if (ft_strncmp(env->key, var_name, len) == 0 && env->key[len] == '\0')
			return (env->value);
		current = current->next;
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
int	manage_variable(char *str, int *i, char *result, t_list *envp)
{
	char	*var_name;
	char	*var_value;
	int		count;

	var_name = extract_var_name(str, i);
	if (!var_name)
		return (0);
	var_value = find_env_value(var_name, envp);
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
