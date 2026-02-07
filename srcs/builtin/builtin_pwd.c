
#include "../../include/minishell.h"

/* affiche le reprtoire dans lequel nouus somme */
void builtin_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return ;
}
