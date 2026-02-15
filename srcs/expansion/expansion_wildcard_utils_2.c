
#include "../../include/minishell.h"

void	free_path_pattern(char *dir_path, char *pattern)
{
	free(dir_path);
	free(pattern);
}

char	*build_full_path(char *dir_path, char *name)
{
	char	*full_path;
	char	*result;

	if (ft_strncmp(dir_path, ".", 2) == 0)
		return (ft_strdup(name));
	full_path = ft_strjoin(dir_path, "/");
	result = ft_strjoin(full_path, name);
	free(full_path);
	return (result);
}

void	free_match_array(char **match, int i)
{
	while (--i >= 0)
		free(match[i]);
	free(match);
}

char	**init_match(char *input, char **dir_path, char **pattern)
{
	char	**match;
	int		count;

	split_path_pattern(input, dir_path, pattern);
	count = count_match(input);
	if (count == 0)
		return (free_path_pattern(*dir_path, *pattern), NULL);
	match = malloc(sizeof(char *) * (count + 1));
	if (!match)
		return (free_path_pattern(*dir_path, *pattern), NULL);
	return (match);
}

int	process_entry(struct dirent *enter, char **match, int *i, char *dir_path)
{
	match[*i] = build_full_path(dir_path, enter->d_name);
	if (!match[*i])
		return (0);
	(*i)++;
	return (1);
}
