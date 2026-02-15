
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
int count_match(char *input)
{
    DIR *dir;
    struct dirent *enter;
    int count;
    char *dir_path;
    char *pattern;
    
    split_path_pattern(input, &dir_path, &pattern);
    count = 0;
    dir = opendir(dir_path);
    if (!dir)
    {
        free(dir_path);
        free(pattern);
        return (0);
    }
    enter = readdir(dir);
    while (enter)
    {
        if (enter->d_name[0] != '.' && match_pattern(pattern, enter->d_name))
            count++;
        enter = readdir(dir);
    }
    closedir(dir);
    free(dir_path);
    free(pattern);
    return (count);
}

/* cree tab avec tt les fichier qui match */
char **get_match(char *input)
{
    DIR *dir;
    struct dirent *enter;
    char **match;
    char *dir_path;
    char *pattern;
    char *full_path;
    int count;
    int i;
    
    split_path_pattern(input, &dir_path, &pattern);
    count = count_match(input);
    i = 0;
    if (count == 0)
    {
        free(dir_path);
        free(pattern);
        return (NULL);
    }
    match = malloc(sizeof(char *) * (count + 1));
    if (!match)
    {
        free(dir_path);
        free(pattern);
        return (NULL);
    }
    dir = opendir(dir_path);
    if (!dir)
    {
        free(match);
        free(dir_path);
        free(pattern);
        return (NULL);
    }
    enter = readdir(dir);
    while (enter)
    {
        if (enter->d_name[0] != '.' && match_pattern(pattern, enter->d_name))
        {
            if (ft_strncmp(dir_path, ".", 2) == 0)
                match[i] = ft_strdup(enter->d_name);
            else
            {
                full_path = ft_strjoin(dir_path, "/");
                match[i] = ft_strjoin(full_path, enter->d_name);
                free(full_path);
            }
            if (!match[i])
            {
                while (--i >= 0)
                    free(match[i]);
                free(match);
                closedir(dir);
                free(dir_path);
                free(pattern);
                return (NULL);
            }
            i++;
        }
        enter = readdir(dir);
    }
    match[i] = NULL;
    closedir(dir);
    free(dir_path);
    free(pattern);
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

/* expand wildcard dans un tab de **av */
char **expand_wildcard(char **av)
{
    char **result;
    char **match;
    int i;
    int j;
    int k;
    int total;
    
    total = 0;
    i = 0;
    k = 0;
    if (!av)
        return (NULL);
    while (av[i])
    {
        if (have_wildcard(av[i]))
        {
            match = get_match(av[i]);
            if (match)
            {
                j = 0;
                while (match[j])
                {
                    total++;
                    free(match[j]);
                    j++;
                }
                free(match);
            }
            else
                total++;
        }
        else
            total++;
        i++;
    }
    result = malloc(sizeof(char *) * (total + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (av[i])
    {
        if (have_wildcard(av[i]))
        {
            match = get_match(av[i]);
            if (match)
            {
                sort_match(match);
                j = 0;
                while (match[j])
                {
                    result[k++] = ft_strdup(match[j]);
                    free(match[j]);
                    j++;
                }
                free(match);
            }
            else
                result[k++] = ft_strdup(av[i]);
        }
        else
            result[k++] = ft_strdup(av[i]);
        i++;
    }
    result[k] = NULL;
    return (result);
}
