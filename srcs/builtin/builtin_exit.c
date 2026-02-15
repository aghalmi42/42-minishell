
#include "../../include/minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void exit_with_error(t_exec_data *data, char *msg, int code)
{
	ft_putstr_fd(msg, 2);
	data->status = code;
	exit(code);
}

void	builtin_exit(t_exec_data *data, t_node *node)
{
	int		cpt;
	int		exit_code;

	cpt = 0;
	while (node->av[cpt])
		cpt++;
	if (cpt > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	if (cpt == 1)
		exit(data->status);
	if (!is_valid_number(node->av[1]))
		exit_with_error(data, "exit : argument numeric is required\n", 2);
	exit_code = ft_atoi(node->av[1]);
	data->status = exit_code;
	exit(exit_code);
}
