
#include "../../include/minishell.h"

/* on verif si la cmd est builtin*/
int builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "pwd", 4) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0 && cmd[2] == '\0')
		return (1);
	return (0);
}

int builtin_parent(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("cd", cmd, 3) && cmd[2] == '\0')
		return (1);
	if (!ft_strncmp("export", cmd, 7) && cmd[6] == '\0')
		return (1);
	if (!ft_strncmp("unset", cmd, 6) && cmd[5] == '\0')
		return (1);
	if (!ft_strncmp("exit", cmd, 5) && cmd[4] == '\0')
		return (1);
	return (0);
}
