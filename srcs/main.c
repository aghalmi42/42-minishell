/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:30:40 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:30:54 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec_data	data;

	(void)argv;
	init_exec_data(&data, envp);
	if (argc != 1)
		return (0);
	while (1)
	{
		set_signal_actions();
		line = read_input_line(&data);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(line, &data);
		free(line);
		clear_all_heredocs(&data);
		gc_delete(&data.gc_head_cmd);
	}
	gc_delete(&data.gc_head_env);
	return (data.status);
}
