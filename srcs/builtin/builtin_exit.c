
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

void exit_msg_error(t_exec_data *data, char *cmd, t_node *node)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("argument numeric is required", 2);
	data->status = 2;
	free_envp(data);
	free_ast(node);
	exit(data->status);
}

void	builtin_exit(t_exec_data *data, t_node *node)
{
	int			cpt;
	long long	exit_code;
	int			error;

	cpt = 0;
	error = 0;
	exit_code = data->status;
	ft_putendl_fd("exit", 2);
	while (node->av[cpt])
		cpt++;
	if (cpt == 1)
		exit_with_one_arg(node, data, exit_code);
	exit_code = ft_atoll(node->av[1], &error);
	if (!is_valid_number(node->av[1]) || error)
		exit_msg_error(data, node->av[1], node);
	exit_code = ft_atoi(node->av[1]);
	if (cpt > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	data->status = exit_code;
	free_envp(data);
	free_ast(node);
	exit(exit_code % 256);
}

void	exit_with_one_arg(t_node *node, t_exec_data *data, long long exit_code)
{
	free_envp(data);
	free_ast(node);
	exit(exit_code);
}

long long	ft_atoll(const char *str, int *error)
{
	unsigned long long	res;
	int					sign;
	int					i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if ((sign == 1 && res > LLONG_MAX) ||
			(sign == -1 && res > (unsigned long long)LLONG_MAX + 1))
		{
			*error = 1;
			return (0);
		}
	}
	return (res * sign);
}
