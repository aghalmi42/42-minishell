/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:51:52 by alex              #+#    #+#             */
/*   Updated: 2026/02/18 15:30:28 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec_data	data;

	(void)argv;
	(void)line;
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
		clear_all_heredocs(&data);
		gc_delete(&data.gc_head_cmd);
	}
	gc_delete(&data.gc_head_env);//free_envp(&data);
	return (data.status);
}

// int	main(void)
// {
// 	t_exec_data data;

// 	init_exec_data(&data, NULL);
// 	char *str = gb_malloc(sizeof(char), &data.gc_head);
// 	(void) str;
// 	gb_delete(&data.gc_head);
// 	return (0);
// }
