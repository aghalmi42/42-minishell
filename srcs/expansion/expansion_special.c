
#include "../../include/minishell.h"

/* gere lexpansion du exit code $? et return nb de char ajt */
int	manage_exit_code(int *i, char *result, t_exec_data *data)
{
	char *exit;
	int count;

	exit = gc_itoa(data->status, &data->gc_head_cmd);
	if (!exit)
		return (0);
	count = copy_to_result(exit, result);
	gc_free_one(&data->gc_head_cmd, exit);
	(*i) += 2;
	return (count);
}

/* gere lexpansion du pid $$ et return nb de char ajt */
int	manage_pid(int *i, char *result, t_list **gc_head_cmd)
{
	char	*pid;
	int		count;

	pid = gc_itoa(getpid(), gc_head_cmd);
	if (!pid)
		return (0);
	count = copy_to_result(pid, result);
	gc_free_one(gc_head_cmd, pid);
	(*i) += 2;
	return (count);
}
