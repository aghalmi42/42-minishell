
#include "../../include/minishell.h"

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

int	handle_cd_error(char *path, t_exec_data *data, char *msg)
{
	(void)path;
	if (msg)
		ft_putendl_fd(msg, 2);
	data->status = 1;
	return (1);
}

int	execute_cd(char *path, t_exec_data *data)
{
	char	new_path[PATH_MAX];

	if (change_directory(path))
	{
		data->status = 1;
		return (1);
	}
	if (getcwd(new_path, sizeof(new_path)) == NULL)
	{
		perror("getcwd");
		data->status = 1;
		return (1);
	}
	change_env_directory(new_path, data);
	data->status = 0;
	return (0);
}

void	update_pwd(t_env *e, char *new_p, t_exec_data *data)
{
	(void) data;
	//gc_free_one(&data->gc_head_env, e->value);
	e->value = new_p;
}

void	update_oldpwd(t_env *e, char *old_path, t_exec_data *data)
{
	(void) data;
	//gc_free_one(&data->gc_head_env, e->value);
	e->value = old_path;
}
