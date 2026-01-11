/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:54:20 by aghalmi           #+#    #+#             */
/*   Updated: 2026/01/11 15:36:42 by aghalmi          ###   ########.fr       */
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
	printf("\ntest avec pipe\n");
	token = lexical_analyzer("ls | grep test");
	print_token(token);
	free_token(token);
	printf("\ntest pipe sans espace\n");
	token = lexical_analyzer("cat|grep|wc");
	print_token(token);
	free_token(token);
	printf("\ntest plusieur pipe\n");
	token = lexical_analyzer("ls -la | grep mini | wc -l");
	print_token(token);
	free_token(token);
	printf("\nredirection simple\n");
	token = lexical_analyzer("cat < input");
	print_token(token);
	free_token(token);
	printf("\ntest redirection output\n");
	token = lexical_analyzer("ls > output");
	print_token(token);
	free_token(token);
	printf("\ntest append\n");
	token = lexical_analyzer("echo test >> file");
	print_token(token);
	free_token(token);
	printf("\ntest heredoc\n");
	token = lexical_analyzer("cat << EOF");
	print_token(token);
	free_token(token);
	printf("\ntest combiner\n");
	token = lexical_analyzer("cat < in | grep test > out");
	print_token(token);
	free_token(token);
	printf("\ntest sans espace\n");
	token = lexical_analyzer("cat<input>output");
	print_token(token);
	free_token(token);
	return (0);
}
