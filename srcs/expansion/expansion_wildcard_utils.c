
#include "../../include/minishell.h"

/* verifie si chaine contien wildcard sans quote */
int have_wildcard(char *str)
{
    int i;
    
    if (!str)
        return (0);
    if (str[0] == '\x02')
        return (0);
    i = 0;
    while (str[i])
    {
        if (str[i] == '*')
        {
            return (1);
        }
        i++;
    }
    return (0);
}

/* fonction de match patterm avec * */
int match_pattern(char *pattern, char *str)
{
    if (*pattern == '\0' && *str == '\0')
        return (1);
    if (*pattern == '*')
    {
        if (match_pattern(pattern + 1, str))
            return (1);
        if (*str != '\0' && match_pattern(pattern, str + 1))
            return (1);
        return (0);
    }
    if (*pattern == *str)
        return (match_pattern(pattern + 1, str + 1));
    return (0);
}

/* extrait le chemin et le patterm duune string comme srcs *.c pour nouus */
int split_path_pattern(char *input, char **dir_path, char **pattern, t_list **gc_head_cmd)
{
    char *last_slash;
    
    last_slash = ft_strrchr(input, '/');
    if (last_slash)
    {
        *dir_path = gc_substr(input, 0, last_slash - input, gc_head_cmd);
        if (!(*dir_path))
            return (0);
        *pattern = gc_strdup(last_slash + 1, gc_head_cmd);
        if (!(*pattern))
            return (0);
    }
    else
    {
        *dir_path = gc_strdup(".", gc_head_cmd);
        if (!(*dir_path))
            return (0);
        *pattern = gc_strdup(input, gc_head_cmd);
        if (!(*pattern))
            return (0);
    }
    return (1);
}

/* compte le nbr de fichier qui match le patternn */
int	count_match(char *input, t_list **gc_head_cmd)
{
	DIR				*dir;
	struct dirent	*enter;
	int				count;
	char			*dir_path;
	char			*pattern;

	if (!split_path_pattern(input, &dir_path, &pattern, gc_head_cmd))
        return (0);
	dir = opendir(dir_path);
	if (!dir)
		return (gc_free_one(gc_head_cmd, dir_path),gc_free_one(gc_head_cmd, pattern), 0);//free_path_pattern(dir_path, pattern)
	count = 0;
	enter = readdir(dir);
	while (enter)
	{
		if (enter->d_name[0] != '.' && match_pattern(pattern, enter->d_name))
			count++;
		enter = readdir(dir);
	}
	closedir(dir);
	free_path_pattern(dir_path, pattern);
	return (count);
}
