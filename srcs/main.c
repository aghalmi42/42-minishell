
#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec_data	data;

	(void)argv;
	init_exec_data(&data, envp);
	if (!data.envp || argc != 1)
		return (0);
	set_signal_actions();
	while (1)
	{
		line = read_input_line();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(line, &data);
		free(line);
	}
	free_envp(&data);
	return (data.status);
}
