/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:12:33 by alex              #+#    #+#             */
/*   Updated: 2026/02/09 08:01:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_export(t_exec_data *data, t_node *node)
{
	t_list	*head;
	t_list	*new_env;
	t_env	*new_key;
	t_env	*search;
	int		i;

	i = 1;
	if (!node->av[1])
		return (builtin_env(data, node, 1));
	if (node->av[1][0] == '-' && node->av[1][1])
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(node->av[1][0], 2);
		ft_putchar_fd(node->av[1][1], 2);
		ft_putendl_fd(": invalid option", 2);
		data->status = 1;
		return ;
	}
	while (node->av[i])
	{
		head = data->envp;
		new_key = split_env_line(node->av[i]);
		//printf("%s ", new_key->value);
		if (!new_key)
			return ;
		if (!check_new_key(new_key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(new_key->key, 2);
			ft_putendl_fd("`: not a valid identifier", 2);
			free(new_key->key);
			free(new_key->value);
			free(new_key);
			i++;
			continue ;
		}
		while(head)
		{
			search = head->content;
			if (!ft_strncmp(new_key->key, search->key, ft_strlen(new_key->key) + 1))
			{
				free(search->value);
				search->value = new_key->value;
				free(new_key->key);
				free(new_key);
				return ;
			}
			head = head->next;
		}
		new_env = ft_lstnew(new_key);
		ft_lstadd_back(&data->envp, new_env);
		i++;
	}
}

int	check_new_key(t_env *env)
{
	int	i;

	i = 1;
	if (env->key[0] != '_' && !ft_isalpha(env->key[0]))
		return (0);
	while(env->key[i])
	{
		if (env->key[i] != '_' && !ft_isalnum(env->key[i]))
			return (0);
		i++;
	}
	return (1);
}
