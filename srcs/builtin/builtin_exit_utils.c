
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
	(void)node;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("argument numeric is required", 2);
	data->status = 2;
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
	exit(data->status);
}

void	final_exit(t_exec_data *data, int cpt, long long exit_code)
{
	if (cpt > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	data->status = exit_code % 256;
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
	exit(data->status);
}

void	exit_with_one_arg(t_node *node, t_exec_data *data, long long exit_code)
{
	(void)node;
	gc_delete(&data->gc_head_cmd);
	gc_delete(&data->gc_head_env);
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
