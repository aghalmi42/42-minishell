/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:32:31 by amoderan          #+#    #+#             */
/*   Updated: 2026/02/04 09:22:44 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    built_in_env(t_exec_data *data)
{
	t_list  *dummy;
	t_env   *e;
	
	dummy = data->envp;
	while(dummy)
	{
		e = dummy->content;
		if (e->value[0] != '\0')
		{
			ft_putstr_fd(e->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(e->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		dummy = dummy->next;
	}
}

void    built_in_export(t_exec_data *data, t_node *node)
{
	t_list	*head;
	t_list	*new_env;
	t_env	*new_key;
	t_env	*search;

	if (!node->av[1])
		return (built_in_env(data));
	head = data->envp;
	new_key = split_env_line(node->av[1]);
	if (!new_key)
		return ;
	if (!check_new_key(new_key))
		return (free(new_key));
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
}

int	check_new_key(t_env *env)
{
	int	i;

	i = 1;
	if (env->key[0] != '_' && ft_isalpha(env->key[0]))
		return (0);
	while(env->key[i])
	{
		if (env->key[0] != '_' && ft_isalnum(env->key[0]))
			return (0);
		i++;
	}
	return (1);
}
// void    built_in_unset(t_exec_data *data)
// {

// }

// void    built_in_exit(t_exec_data *data)
// {
	
// }