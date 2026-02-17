
#include "../../include/minishell.h"

int	fill_matches(DIR *dir, char **match, char *dir_path, char *pattern, t_list **gc_head)
{
	struct dirent	*enter;
	int				i;

	i = 0;
	enter = readdir(dir);
	while (enter)
	{
		if (enter->d_name[0] != '.' && match_pattern(pattern, enter->d_name))
			if (!process_entry(enter, match, &i, dir_path, gc_head))
				return (-1);
		enter = readdir(dir);
	}
	match[i] = NULL;
	return (0);
}

char	**get_match(char *input, t_list **gc_head)
{
	DIR		*dir;
	char	**match;
	char	*dir_path;
	char	*pattern;

	match = init_match(input, &dir_path, &pattern, gc_head);
	if (!match)
		return (NULL);
	dir = opendir(dir_path);
	if (!dir)
		return (gc_free_one(gc_head, dir_path),gc_free_one(gc_head, pattern), gc_free_one(gc_head, match),free(match), free_path_pattern(dir_path, pattern), NULL);
	if (fill_matches(dir, match, dir_path, pattern, gc_head) == -1)
		return (free_match_array(match, 0), closedir(dir),
			free_path_pattern(dir_path, pattern), NULL);
	closedir(dir);
	free_path_pattern(dir_path, pattern);
	return (match);
}

/* trie les resu par ordre alpha */
void sort_match(char **match)
{
    int i;
    int j;
    char *tmp;
    
    i = 0;
    if (!match)
        return ;
    while (match[i])
    {
        j = i + 1;
        while (match[j])
        {
            if (ft_strncmp(match[i], match[j], 1000) > 0)
            {
                tmp = match[i];
                match[i] = match[j];
                match[j] = tmp;
            }
            j++;
        }
        i++;
    }
}
