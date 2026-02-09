/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:12:33 by alex              #+#    #+#             */
/*   Updated: 2026/02/09 02:20:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_export(t_exec_data *data, t_node *node)
{
	t_list	*head;
	t_list	*new_env;
	t_env	*new_key;
	t_env	*search;

	if (!node->av[1])
		return (builtin_env(data, 1));
	head = data->envp;
	new_key = split_env_line(node->av[1]);
	//printf("%s ", new_key->value);
	if (!new_key)
		return ;
	if (!check_new_key(new_key))
		return (perror("not a valid identifier"), free(new_key));
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
