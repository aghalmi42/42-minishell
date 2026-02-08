
#include "../../include/minishell.h"

/* affiche le reprtoire dans lequel nouus somme */
void builtin_pwd(t_exec_data *data, t_node *node)
{
	char cwd[PATH_MAX];
	int i;

	i = 0;
	while(node->av && node->av[i])
	{
		if (node->av[i][0] == '-')
		{
			ft_putstr_fd("pwd : ", 2);
			ft_putstr_fd(node->av[i], 2);
			ft_putendl_fd(" invalid option", 2);
			data->status = 1;
			return ;
		}
		i++;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		data->status = 1;
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	data->status = 0;
}
