
#include "../../include/minishell.h"

/* gere lexpansion du exit code $? et return nb de char ajt */
int	manage_exit_code(int *i, char *result)
{
	result[0] = '0';
	(*i) += 2;
	return (1);
}

/* gere lexpansion du pid $$ et return nb de char ajt */
int	manage_pid(int *i, char *result)
{
	char	*pid;
	int		count;

	pid = ft_itoa(getpid());
	count = copy_to_result(pid, result);
	free(pid);
	(*i) += 2;
	return (count);
}
