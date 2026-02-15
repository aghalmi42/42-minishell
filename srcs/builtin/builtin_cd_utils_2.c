
#include "../../include/minishell.h"

void	update_env_vars(t_exec_data *data, char *new_p, char *old_path)
{
	t_list	*env;
	t_env	*e;

	env = data->envp;
	while (env)
	{
		e = env->content;
		if (!ft_strncmp(e->key, "PWD", 4))
			update_pwd(e, new_p);
		else if (!ft_strncmp(e->key, "OLDPWD", 7))
			update_oldpwd(e, old_path);
		env = env->next;
	}
}

void	change_env_directory(char *new_path, t_exec_data *data)
{
	char	*old_path;
	char	*new_p;

	old_path = search_env_value(data, "PWD");
	if (!old_path)
		old_path = ft_strdup("");
	if (!old_path)
	{
		data->status = 1;
		return ;
	}
	new_p = ft_strdup(new_path);
	if (!new_p)
	{
		free(old_path);
		data->status = 1;
		return ;
	}
	update_env_vars(data, new_p, old_path);
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
	{
		ft_putendl_fd("cd : HOME is not set", 2);
		data->status = 1;
	}
	return (path);
}

/* on va determiner le chemin de la dest */
char *search_cd_path(t_exec_data *data, t_node *node)
{
	char *oldpwd;

	if (!node->av[1])
		return (search_home_path(data));
	else if (ft_strncmp(node->av[1], "-", 2) == 0 && node->av[1][1] == '\0')
	{
		oldpwd = search_env_value(data, "OLDPWD");
		if (!oldpwd)
		{
			ft_putendl_fd("cd : OLDPWD is not set", 2);
			data->status = 1;
			return (NULL);
		}
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		return (oldpwd);
	}
	else
		return (ft_strdup(node->av[1]));
}
