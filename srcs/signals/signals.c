/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:27:49 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:30:13 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_status;

void	handle_sigint(int signal)
{
	g_status = signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_here_doc(int signal)
{
	g_status = signal;
}

void	handle_sigint_fork(int signal)
{
	g_status = signal;
}

int	check_readline_sigint(void)
{
	if (g_status == SIGINT)
		rl_done = 1;
	return (0);
}
