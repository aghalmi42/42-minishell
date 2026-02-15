
#include "../../include/minishell.h"

void	builtin_export(t_exec_data *data, t_node *node)
{
	int	i;

	if (!node->av[1])
		return (builtin_env(data, node, 1));
	if (node->av[1][0] == '-' && node->av[1][1])
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(node->av[1][0], 2);
		ft_putchar_fd(node->av[1][1], 2);
		ft_putendl_fd(": invalid option", 2);
		data->status = 1;
		return ;
	}
	i = 1;
	while (node->av[i])
	{
		process_export_arg(data, node->av[i]);
		i++;
	}
}
