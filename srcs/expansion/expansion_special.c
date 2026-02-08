
#include "../../include/minishell.h"

/* gere lexpansion du exit code $? et return nb de char ajt */
int	manage_exit_code(int *i, char *result, t_exec_data *data)
{
	char *exit;
	int count;

	exit = ft_itoa(data->status);
	if (!exit)
		return (0);
	count = copy_to_result(exit, result);
	free(exit);
	(*i) += 2;
	return (count);
}

/* gere lexpansion du pid $$ et return nb de char ajt */
int	manage_pid(int *i, char *result)
{
	char	*pid;
	int		count;

	pid = ft_itoa(getpid());
	if (!pid)
		return (0);
	count = copy_to_result(pid, result);
	free(pid);
	(*i) += 2;
	return (count);
}
