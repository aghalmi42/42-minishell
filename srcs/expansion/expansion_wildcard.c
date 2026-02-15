
#include "../../include/minishell.h"

int	count_expanded_size(char **av)
{
	char	**match;
	int		i;
	int		j;
	int		total;

	total = 0;
	i = 0;
	while (av[i])
	{
		if (have_wildcard(av[i]))
		{
			match = get_match(av[i]);
			if (match)
			{
				j = 0;
				while (match[j])
					free(match[j++]);
				free(match);
				total += j;
			}
			else
				total++;
		}
		else
			total++;
		i++;
	}
	return (total);
}

void	add_matches_to_result(char **result, int *k, char **match)
{
	int	j;

	sort_match(match);
	j = 0;
	while (match[j])
	{
		result[(*k)++] = ft_strdup(match[j]);
		free(match[j]);
		j++;
	}
	free(match);
}

void	fill_result(char **result, char **av)
{
	char	**match;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (av[i])
	{
		if (have_wildcard(av[i]))
		{
			match = get_match(av[i]);
			if (match)
				add_matches_to_result(result, &k, match);
			else
				result[k++] = ft_strdup(av[i]);
		}
		else
			result[k++] = ft_strdup(av[i]);
		i++;
	}
	result[k] = NULL;
}

char	**expand_wildcard(char **av)
{
	char	**result;
	int		total;

	if (!av)
		return (NULL);
	total = count_expanded_size(av);
	result = malloc(sizeof(char *) * (total + 1));
	if (!result)
		return (NULL);
	fill_result(result, av);
	return (result);
}
