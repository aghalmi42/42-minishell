
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
void split_path_pattern(char *input, char **dir_path, char **pattern)
{
    char *last_slash;
    
    last_slash = ft_strrchr(input, '/');
    if (last_slash)
    {
        *dir_path = ft_substr(input, 0, last_slash - input);
        *pattern = ft_strdup(last_slash + 1);
    }
    else
    {
        *dir_path = ft_strdup(".");
        *pattern = ft_strdup(input);
    }
}

/* compte le nbr de fichier qui match le patternn */
int	count_match(char *input)
{
	DIR				*dir;
	struct dirent	*enter;
	int				count;
	char			*dir_path;
	char			*pattern;

	split_path_pattern(input, &dir_path, &pattern);
	dir = opendir(dir_path);
	if (!dir)
		return (free_path_pattern(dir_path, pattern), 0);
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
