
#include "../../include/minishell.h"

/* verif si c avec uune option -n */
int n_option(char *av)
{
    int i;

    i = 1;
    if (!av || av[0] != '-' || av[1] != 'n')
        return (0);
    while(av[i])
    {
        if (av[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

/* affiche les argv avec gestion option -n */
int builtin_echo(char **av)
{
    int i;
    int line;

    i = 1;
    line = 1;
    while(av[i] && n_option(av[i]))
    {
        line = 0;
        i++;
    }
    while(av[i])
    {
        ft_putstr_fd(av[i], STDOUT_FILENO);
        if (av[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (line)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}
