
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
	data.status = 0;
	data.head = NULL;
	data.gc_head = NULL;
	set_signal_actions();
	if (argc == 1)
	{
		while(1)
		{
			token = NULL;
			ast = NULL;
			if (isatty(STDIN_FILENO))
				line = readline("minishell$ ");
			else
			{
				char *tmp = get_next_line(STDIN_FILENO);
				if (!tmp)
					break ;
				line = ft_strtrim(tmp, "\n");
				free(tmp);
			}
			if (!line)
			{
				printf("exit\n");
				break ;
			}
			if (isatty(STDIN_FILENO))
				add_history(line);
			token = lexical_analyzer(line);
			if (token)
			{
				expand_token(token, &data);
				ast = parsing(token, &data);
				if (ast)
				{
					if (search_here_doc_to_execute(ast, &data) == -1)
					{
						free_ast(ast);
						free(line);
						continue ;
					}
					data.is_fork = 0;
					token = NULL;
					//print_ast(ast, 0);
					exec_main(ast, &data);
					free_ast(ast);
					ast = NULL;
				}
				else
				{
					free_token(token);
					token = NULL;
				}
			}
			if (token)
			{
				free_token(token);
				token = NULL;
			}
			if (ast)
			{
				free_ast(ast);
				ast = NULL;
			}
			free(line);
			//printf("data.status :%d\n", data.status);
		}
		free_envp(&data);
	}
	return (data.status);
}

// int main (void)
// {
// 	t_exec_data *data = malloc(sizeof(t_exec_data));
// 	printf("%p\n", data);
// 	if (fork() == 0)
// 	{
// 		printf("%p\n", data);
// 		free(data);
// 		exit(126);
// 	}
// 	data->is_fork = 12;
// 	printf("%d\n", data->is_fork);
// 	t_list *test = ft_lstnew(NULL);
// 	data->envp = test;
// 	free(data->envp);
// 	free(data);
	
// }

