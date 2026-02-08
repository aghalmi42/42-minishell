
#include "../../include/minishell.h"

/* recuperer le chemin HOME */
// char *search_home_path(char **env)
// {
// 	char *path;
	
// 	path = find_env_value("HOME", env);
// 	if (!path)
// 		ft_putendl_fd("cd : HOME is not set", 2);
// 	return (path);
// }

// /* recupere le chemin OLDPWD et lafficher */
// char *search_oldpwd_path(char **env)
// {
// 	char *path;

// 	path = find_env_value("OLDPWD", env);
// 	if (!path)
// 	{
// 		ft_putendl_fd("cd : OLDPWD is not set", 2);
// 		return (NULL);
// 	}
// 	ft_putendl_fd(path, STDOUT_FILENO);
// 	return (path);
// }

// /* on va determiner le chemin de la dest */
// char *search_cd_path(char **av, char **env)
// {
// 	if (!av[1])
// 		return (search_home_path(env));
// 	else if (ft_strncmp(av[1], "-", 2) == 0 && av[1][1] == '\0')
// 		return (search_oldpwd_path(env));
// 	else
// 		return (av[1]);
// }



// /* fonction principal de builtin cd */
// int builtin_cd(char **av, char **env)
// {
// 	char *path;

// 	path = search_cd_path(av, env);
// 	if (!path)
// 		return (1);
// 	return (change_directory(path));
// }


/* change de repertoire */
int change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

void	builtin_cd(t_exec_data *data, t_node *node)
{
	char	*path;
	char	new_path[PATH_MAX];

	path = search_cd_path(data, node);
	if (!path)
		return ;
	if (!change_directory(path))
	{
		if (getcwd(new_path, sizeof(new_path)) == NULL)
		{
			perror("pwd");
			ft_putstr_fd("Bof\n", 1);
			return ;
		}
		change_env_directory(new_path, data);
	}
	free(path);
}

void	change_env_directory(char *new_path, t_exec_data *data)
{
	t_list	*env;
	t_env	*e;
	char	*old_path;
	char	*new_p;

	old_path = search_env_value(data, "PWD");
	if (!old_path)
		return ;
	new_p = ft_strdup(new_path);
	if (!new_p)
	{
		data->status = 1;
		return (free(old_path));
	}
	env = data->envp;
	while (env)
	{
		e = env->content;
		if (!ft_strncmp(e->key, "PWD", 4))
		{
			free(e->value);
			e->value = new_p;
		}
		if (!ft_strncmp(e->key, "OLDPWD", 7))
		{
			free(e->value);
			e->value = old_path;
		}
		env = env->next;
	}
}

char	*search_env_value(t_exec_data *data, char *search)
{
	t_list	*cur;
	t_env	*env;
	char	*value;

	cur = data->envp;
	while (cur)
	{
		env = cur->content;
		if (!ft_strncmp(env->key, search, ft_strlen(search) + 1))
		{
			value = ft_strdup(env->value);
			if (!value)
			{
				data->status = 1;
				return (NULL);
			}
			return (value);
		}
		cur = cur->next;
	}
	return (NULL);
}
char *search_home_path(t_exec_data *data)
{
	char *path;

	path = search_env_value(data, "HOME");
	if (!path)
		ft_putendl_fd("cd : HOME is not set", 2);
	return (path);
}

/* on va determiner le chemin de la dest */
char *search_cd_path(t_exec_data *data, t_node *node)
{
	if (!node->av[1])
		return (search_home_path(data));
	else if (ft_strncmp(node->av[1], "-", 2) == 0 && node->av[1][1] == '\0')
		return (search_env_value(data, "OLDPWD"));
	else
		return (ft_strdup(node->av[1]));
}

// char	*find_home_value(t_exec_data *data, t_list *envp)
// {
// 	t_list	*cur;
// 	t_env	*env;
// 	char	*home;

// 	cur = envp;
// 	while (cur)
// 	{
// 		env = cur->content;
// 		if (!ft_strncmp(env->key, "HOME", 5))
// 		{
// 			home = ft_strdup(env->value);
// 			if (!home)
// 			{
// 				data->status = 1;
// 				return (NULL);
// 			}
// 			return (home);
// 		}
// 		cur = cur->next;
// 	}
// 	return (NULL);
// }

/* recupere le chemin OLDPWD et lafficher */
// char *search_oldpwd_path(t_exec_data *data, t_list *envp)
// {
// 	t_list	*cur;
// 	t_env	*env;
// 	char	*oldpwd;

// 	cur = envp;
// 	while (cur)
// 	{
// 		env = cur->content;
// 		if (!ft_strncmp(env->key, "OLDPWD", 7))
// 		{
// 			oldpwd = ft_strdup(env->value);
// 			if (!oldpwd)
// 			{
// 				data->status = 1;
// 				return (NULL);
// 			}
// 			return (oldpwd);
// 		}
// 		cur = cur->next;
// 	}
// 	return (NULL);
// }

