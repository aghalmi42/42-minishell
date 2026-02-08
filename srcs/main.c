
#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	char		*line;
	t_token		*token;
	t_node		*ast;
	t_exec_data	data;

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
					data.is_fork = 0;
					print_ast(ast, 0);
					exec_main(ast, &data);
					free_ast(ast);
				}
				free_token(token);
			}
			free(line);
			printf("data.status :%d\n", data.status);
		}
		free_envp(&data);
	}
}

