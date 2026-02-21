/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_here_doc_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:34:32 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:34:32 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_next_line_hd(int fd, t_exec_data *data)
{
	char	*tmp;

	if (g_status == SIGINT)
	{
		rl_event_hook = NULL;
		close(fd);
		clear_all_heredocs(data);
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
		exit(130);
	}
	if (isatty(STDIN_FILENO))
		return (readline("heredoc> "));
	tmp = get_next_line(STDIN_FILENO);
	if (!tmp)
		return (NULL);
	if (tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = '\0';
	return (tmp);
}

void	loop_here_doc(char *limiter, int fd, t_exec_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line_hd(fd, data);
		if (!line)
		{
			ft_putstr_fd("minishell: warning:", 2);
			ft_putstr_fd(" here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}
