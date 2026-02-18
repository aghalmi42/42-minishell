/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:52:15 by alex              #+#    #+#             */
/*   Updated: 2026/02/18 17:37:17 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile	sig_atomic_t	s_status;

void	handle_sigint(int	signal)
{
	s_status = 128 + signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_here_doc(int	signal)
{
	s_status = signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigint_fork(int	signal)
{
	s_status = signal;
	write(STDOUT_FILENO, "\n", 1);
}

int	check_readline_sigint(void)
{
	if (s_status == SIGINT)
		rl_done = 1;
	return (0);
}
