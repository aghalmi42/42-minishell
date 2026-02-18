
#include "../../include/minishell.h"

// void	exec_one_cmd(t_node *node, char **envp, t_list **gc_head_cmd)
// {
// 	char	*path_cmd;

// 	path_cmd = path_to_find(node->av[0], envp, gc_head_cmd);
// 	if (!path_cmd)
// 		return ;
// 	if (fork() == 0)
// 	{
// 		if (execve(path_cmd, node->av, envp) == - 1)
// 		{
// 			perror("execve fail");
// 			gc_delete(gc_head_cmd);
// 			gc_delete(&data->gc_head_env);
// 			exit(126);
// 		}
// 	}
// 	wait(NULL);
// 	//free(path_cmd);
// }

void	execute_in_child(char *path_cmd, t_node *node, char **envp, t_exec_data *data)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
	if (execve(path_cmd, node->av, envp) == -1)
	{
		perror("execve fail");
		// free_ast(node);
		// free_envp(data);
		// free_split(envp);
		gc_delete(&data->gc_head_env);
		gc_delete(&data->gc_head_cmd);
		exit(126);
	}
}

void	exec_one_cmd_lst(t_node *node, t_exec_data *data)
{
	char	*path_cmd;
	char	**envp;
	pid_t	pid;

	if (is_a_built_in(node->av[0]))
		return ;
	path_cmd = path_to_find_lst(node->av[0], data);
	if (!path_cmd)
	{
		data->status = 127;
		return ;
	}
	envp = getenv_to_str(data->envp, &data->gc_head_cmd);
	if (!envp)
		return (gc_free_one(&data->gc_head_cmd, path_cmd));
	pid = fork();
	if (pid == 0)
		execute_in_child(path_cmd, node, envp, data);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	waitpid(pid, &data->status, 0);
	//gc_free_one(&data->gc_head_cmd, path_cmd);//free(path_cmd);
	//free_split(envp);
	set_signal_actions();
}
