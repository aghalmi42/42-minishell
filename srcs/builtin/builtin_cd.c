
#include "../../include/minishell.h"

/* recuperer le chemin HOME */
char *search_home_path(char **env)
{
	char *path;

	path = find_env_value("HOME", env);
	if (!path)
		ft_putendl_fd("cd : HOME is not set", 2);
	return (path);
}

/* recupere le chemin OLDPWD et lafficher */
char *search_oldpwd_path(char **env)
{
	char *path;

	path = find_env_value("OLDPWD", env);
	if (!path)
	{
		ft_putendl_fd("cd : OLDPWD is not set", 2);
		return (NULL);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	return (path);
}

/* on va determiner le chemin de la dest */
char *search_cd_path(char **av, char **env)
{
	if (!av[1])
		return (search_home_path(env));
	else if (ft_strncmp(av[1], "-", 2) == 0 && av[1][1] == '\0')
		return (search_oldpwd_path(env));
	else
		return (av[1]);
}

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

/* fonction principal de builtin cd */
int builtin_cd(char **av, char **env)
{
	char *path;

	path = search_cd_path(av, env);
	if (!path)
		return (1);
	return (change_directory(path));
}
