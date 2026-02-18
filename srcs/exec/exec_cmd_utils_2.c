
#include "../../include/minishell.h"

void	handle_builtin(t_node *node, t_exec_data *data)
{
	exec_built_in(node->av[0], data, node);
	if (data->is_fork)
	{
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
		exit(data->status);
	}
		
}

void	handle_path_error(t_node *node, t_exec_data *data)
{
	(void) node;
	data->status = 127;
	if (data->is_fork)
	{
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
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
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
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
			gc_delete(&data->gc_head_cmd);
			gc_delete(&data->gc_head_env);
			exit(1);
		}
		return ;
	}
	
	if (execve(path_cmd, node->av, envp) == -1)
	{
		perror("execve");
		gc_delete(&data->gc_head_cmd);
		gc_delete(&data->gc_head_env);
		exit(126);
	}
}

void	run_external_cmd(t_node *node, t_exec_data *data)
{
	char	*path_cmd;

	path_cmd = path_to_find_lst(node->av[0], data);
	if (!path_cmd)
	{
		handle_path_error(node, data);
		return ;
	}
	if (is_a_directory(path_cmd))
	{
		handle_directory_error(path_cmd, node, data);
		return ;
	}
	execute_command(path_cmd, node, data);
}
