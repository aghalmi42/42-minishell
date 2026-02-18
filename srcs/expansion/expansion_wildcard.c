
#include "../../include/minishell.h"

int	count_expanded_size(char **av, t_list **gc_head_cmd)
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
			match = get_match(av[i], gc_head_cmd);
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

void	add_matches_to_result(char **result, int *k, char **match, t_list **gc_head_cmd)
{
	int	j;

	sort_match(match);
	j = 0;
	while (match[j])
	{
		result[(*k)++] = gc_strdup(match[j], gc_head_cmd);
		gc_free_one(gc_head_cmd, match[j]);//free(match[j]);
		j++;
	}
	gc_free_one(gc_head_cmd, match);//free(match);
}

void	fill_result(char **result, char **av, t_list **gc_head_cmd)
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
			match = get_match(av[i], gc_head_cmd);
			if (match)
				add_matches_to_result(result, &k, match, gc_head_cmd);
			else
			{
				result[k++] = gc_strdup(av[i], gc_head_cmd);
				if (!result[k - 1])
					return ;
			}

		}
		else
		{
			result[k++] = gc_strdup(av[i], gc_head_cmd);
			if (!result[k - 1])
				return ;
		}

		i++;
	}
	result[k] = NULL;
}

char	**expand_wildcard(char **av, t_list **gc_head_cmd)
{
	char	**result;
	int		total;

	if (!av)
		return (NULL);
	total = count_expanded_size(av, gc_head_cmd);
	result = gc_malloc(sizeof(char *) * (total + 1), gc_head_cmd);
	if (!result)
		return (NULL);
	fill_result(result, av, gc_head_cmd);
	return (result);
}
