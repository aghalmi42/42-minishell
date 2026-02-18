
#include "../../include/minishell.h"

void	free_path_pattern(char *dir_path, char *pattern)
{
	free(dir_path);
	free(pattern);
}

char	*build_full_path(char *dir_path, char *name, t_list **gc_head_cmd)
{
	char	*full_path;
	char	*result;

	if (ft_strncmp(dir_path, ".", 2) == 0)
		return (gc_strdup(name, gc_head_cmd));
	full_path = gc_strjoin(dir_path, "/", gc_head_cmd);
	result = gc_strjoin(full_path, name, gc_head_cmd);
	gc_free_one(gc_head_cmd, full_path);//free(full_path);
	return (result);
}

void	free_match_array(char **match, int i)
{
	while (--i >= 0)
		free(match[i]);
	free(match);
}

char	**init_match(char *input, char **dir_path, char **pattern, t_list **gc_head_cmd)
{
	char	**match;
	int		count;

	if (!split_path_pattern(input, dir_path, pattern, gc_head_cmd))
		return (NULL);
	count = count_match(input, gc_head_cmd);
	if (count == 0)
		return (gc_free_one(gc_head_cmd, dir_path),gc_free_one(gc_head_cmd, pattern), NULL);//free_path_pattern(*dir_path, *pattern)
	match = gc_malloc(sizeof(char *) * (count + 1), gc_head_cmd);
	if (!match)
		return (free_path_pattern(*dir_path, *pattern), NULL);
	return (match);
}

int	process_entry(struct dirent *enter, char **match, int *i, char *dir_path, t_list **gc_head_cmd)
{
	match[*i] = build_full_path(dir_path, enter->d_name, gc_head_cmd);
	if (!match[*i])
		return (0);
	(*i)++;
	return (1);
}
