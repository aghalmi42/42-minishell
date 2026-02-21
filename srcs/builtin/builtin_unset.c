/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:21:54 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:22:15 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_unset_error(char *key)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
	return (1);
}

void	remove_env_key(t_exec_data *data, char *key)
{
	t_list	*curr;
	t_list	*prev;
	t_env	*env;

	prev = NULL;
	curr = data->envp;
	while (curr)
	{
		env = curr->content;
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
		{
			if (prev == NULL)
				data->envp = curr->next;
			else
				prev->next = curr->next;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	check_new_unset(char *env)
{
	int	i;

	i = 1;
	if (env[0] != '_' && !ft_isalpha(env[0]))
		return (0);
	while (env[i])
	{
		if (env[i] != '_' && !ft_isalnum(env[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_unset(t_exec_data *data, t_node *node)
{
	int	i;

	if (!data->envp)
		return ;
	i = 1;
	while (node->av[i])
	{
		if (!check_new_unset(node->av[i]))
		{
			handle_unset_error(node->av[i]);
			i++;
			continue ;
		}
		remove_env_key(data, node->av[i]);
		i++;
	}
}
