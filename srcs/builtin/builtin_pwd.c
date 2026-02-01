
#include "../../include/minishell.h"

/* affiche le reprtoire dans lequuel nouus somme */
int builtin_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("pwd");
        return (1);
    }
    ft_putendl_fd(cwd, STDOUT_FILENO);
    return (0);
}
