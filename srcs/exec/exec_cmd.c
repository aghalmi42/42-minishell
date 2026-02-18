
#include "../../include/minishell.h"

void	handle_builtin(t_node *node, t_exec_data *data)
{
	exec_built_in(node->av[0], data, node);
	if (data->is_fork)
		exit(data->status);
}

void	handle_path_error(t_node *node, t_exec_data *data)
{
	(void) node;
	data->status = 127;
	if (data->is_fork)
	{
		// free_ast(node);
		// free_envp(data);
		gc_delete(&data->gc_head_cmd);
		exit(127);
	}
}

void	handle_directory_error(char *path, t_node *node, t_exec_data *data)
{
	(void) node;
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Is a directory", 2);
	data->status = 126;
	if (data->is_fork)
	{
		// free_ast(node);
		// free_envp(data);
		// free(path);
		gc_delete(&data->gc_head_cmd);
		exit(126);
	}
}

void	execute_command(char *path_cmd, t_node *node, t_exec_data *data)
{
	char	**envp;
	(void) node;

	envp = getenv_to_str(data->envp, &data->gc_head_cmd);
	if (!envp)
	{
		free(path_cmd);
		data->status = 1;
		if (data->is_fork)
		{
			// free_envp(data);
			// free_ast(node);
			gc_delete(&data->gc_head_cmd);
			exit(1);
		}
		return ;
	}
	
	if (execve(path_cmd, node->av, envp) == -1)
	{
		perror("execve");
		// free(path_cmd);
		// free_split(envp);
		gc_delete(&data->gc_head_cmd);
		exit(126);
	}
}

void	exec_cmd(t_node *node, t_exec_data *data)
{
	char	*path_cmd;
	char	**expand_av;

	if (!node->av || !node->av[0] || node->av[0][0] == '\0')
	{
		data->status = 0;
		if (data->is_fork)
		{
			// free_envp(data);
			// free_ast(node);
			gc_delete(&data->gc_head_cmd);
			exit(0);
		}
		return ;
	}
	expand_av = expand_wildcard(node->av, &data->gc_head_cmd);
	if (expand_av)
	{
		free_split(node->av);
		node->av = expand_av;
	}
	
	if (is_a_built_in(node->av[0]))
		return (handle_builtin(node, data));
	
	path_cmd = path_to_find_lst(node->av[0], data);
	if (!path_cmd)
		return (handle_path_error(node, data));
	
	if (is_a_directory(path_cmd))
		return (handle_directory_error(path_cmd, node, data));
	
	execute_command(path_cmd, node, data);
}
