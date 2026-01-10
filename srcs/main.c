/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:54:20 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/10 11:58:12 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_token	*token;

	printf("test ls -la\n");
	token = lexical_analyzer("ls -la");
	print_token(token);
	free_token(token);
	printf("\ntest echo hello world\n");
	token = lexical_analyzer("echo hello world");
	print_token(token);
	free_token(token);
	printf("\ntest avec tabulation\n");
	token = lexical_analyzer("cat\tcat\tfile.txt");
	print_token(token);
	free_token(token);
	return (0);
}
