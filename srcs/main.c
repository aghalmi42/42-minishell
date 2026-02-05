
#include "../include/minishell.h"

/*
	MAIN DE TEST POUR LE LEXICALANALYZER

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
	printf("\ntest guillemet double\n");
	token = lexical_analyzer("echo \"hello world\"");
	print_token(token);
	free_token(token);
	printf("\ntest quote simple\n");
	token = lexical_analyzer("echo 'hello world'");
	print_token(token);
	free_token(token);
	printf("\ntest quuote avec metachar\n");
	token = lexical_analyzer("echo 'ls | grep'");
	print_token(token);
	free_token(token);
	printf("\ntest melange des 2\n");
	token = lexical_analyzer("echo \"hello\"world'test'");
	print_token(token);
	free_token(token);
	printf("\ntest quote vide \n");
	token = lexical_analyzer("echo \"\" ''");
	print_token(token);
	free_token(token);
	return (0);
}

*/

// int	main(void)
// {
// 	char	*line;
// 	t_token	*token;
// 	t_node	*ast;

// 	line = "echo \"hello";
// 	token = lexical_analyzer(line);
// 	if (token == NULL)
// 	{
// 		printf("minishell: syntax error unclosed quote\n");
// 		return (2);
// 	}
// 	ast = parsing(token);
// 	print_ast(ast, 0);
// 	free_ast(ast);
// 	free_token(token);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*line;
	t_token	*token;
	t_node	*ast;
	t_exec_data data;

	data.envp = envp_to_lst(envp);
	if (!data.envp)
		return (0);
	set_signal_actions();
	if (argc == 1 && isatty(STDIN_FILENO))
	{
		while(1)
		{
			line = readline("$>");
			if (!line)
				break;
			add_history(line);
			token = lexical_analyzer(line);
			if (token)
			{
				ast = parsing(token);
				if (ast)
				{
					if (search_here_doc_to_execute(ast, &data) == -1)
					{
						free_ast(ast);
						free_token(token);
						free(line);
						continue ;
					}
					exec_main(ast, &data);
					// if(ast->type == NODE_PIPE)
					// 	exec_main(ast, &data);
					// else
					// 	exec_one_cmd_lst(ast, &data);
					free_ast(ast);
				}
				free_token(token);
			}
			free(line);
		}
		free_envp(&data);
	}
}

// int	main(void)
// {
// 	char	*line;
// 	t_token	*token;
// 	t_node	*ast;

// 	printf("Test 1 ls -la\n");
// 	line = "ls -la";
// 	token = lexical_analyzer(line);
// 	ast = parsing(token);
// 	print_ast(ast, 0);
// 	free_ast(ast);
// 	free_token(token);
// 	printf("\n Test 2 ls | grep test\n");
// 	line = "ls | grep test";
// 	token = lexical_analyzer(line);
// 	ast = parsing(token);
// 	print_ast(ast, 0);
// 	free_ast(ast);
// 	free_token(token);
// 	printf("\nTest 3 cat < input\n");
// 	line = "cat < input";
// 	token = lexical_analyzer(line);
// 	ast = parsing(token);
// 	print_ast(ast, 0);
// 	free_ast(ast);
// 	free_token(token);
// 	printf("\nTest 4 ls > output\n");
// 	line = "ls > output";
// 	token = lexical_analyzer(line);
// 	ast = parsing(token);
// 	print_ast(ast, 0);
// 	free_ast(ast);
// 	free_token(token);
// 	printf("\nTest 5 cat < in | grep test > out\n");
// 	line = "cat < in | grep test > out";
// 	token = lexical_analyzer(line);
// 	ast = parsing(token);
// 	print_ast(ast, 0);
// 	free_ast(ast);
// 	free_token(token);
// 	return (0);
// }

