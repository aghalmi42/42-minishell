
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
	if (msg)
		ft_putendl_fd(msg, 2);
	if (path)
		free(path);
	data->status = 1;
	return (1);
}

int	execute_cd(char *path, t_exec_data *data)
{
	char	new_path[PATH_MAX];

	if (change_directory(path))
		return (handle_cd_error(path, data, NULL));
	if (getcwd(new_path, sizeof(new_path)) == NULL)
	{
		perror("getcwd");
		return (handle_cd_error(path, data, NULL));
	}
	change_env_directory(new_path, data);
	free(path);
	data->status = 0;
	return (0);
}

void	update_pwd(t_env *e, char *new_p)
{
	free(e->value);
	e->value = new_p;
}

void	update_oldpwd(t_env *e, char *old_path)
{
	free(e->value);
	e->value = old_path;
}
