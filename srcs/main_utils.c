/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:52:04 by alex              #+#    #+#             */
/*   Updated: 2026/02/16 01:52:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_input_line(void)
{
	char	*line;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		line = readline("minishell$ ");
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (!tmp)
			return (NULL);
		line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	return (line);
}

int	process_heredocs(t_node *ast, t_exec_data *data)
{
	int	index;

	index = 0;
	if (search_here_doc_to_execute(ast, data, &index) == -1)
	{
		//free_ast(ast);
		//free(line);
		clear_all_heredocs(data);
		gc_delete(&data->gc_head_cmd);
		return (0);
	}
	return (1);
}

void	execute_ast(t_node *ast, t_exec_data *data)
{
	data->is_fork = 0;
	exec_main(ast, data);
	//free_ast(ast);
	//free_here_doc_list(data->head);
	data->head = NULL;
}

void	process_line(char *line, t_exec_data *data)
{
	t_token	*token;
	t_node	*ast;
	(void) ast;
	(void) data;

	if (isatty(STDIN_FILENO))
		add_history(line);
	token = lexical_analyzer(line, &data->gc_head_cmd);
	if (!token)
		return ;
	expand_token(token, data);
	ast = parsing(token, data);
	if (ast)
	{
		if (process_heredocs(ast, data))
			printf("good here_doc\n");
			//execute_ast(ast, data);
	}
	//free_token(token);
	//token = NULL;
	//gc_delete(&data->gc_head);
}

void	init_exec_data(t_exec_data *data, char **envp)
{
	data->gc_head_env= NULL;
	data->gc_head_cmd = NULL;
	data->envp = envp_to_lst(envp, &data->gc_head_env);
	data->status = 0;
	data->head = NULL;
}
