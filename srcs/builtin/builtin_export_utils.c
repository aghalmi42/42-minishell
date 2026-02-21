/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:27:00 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:27:00 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_export_error(t_env *new_key, t_exec_data *data)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(new_key->key, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
	data->status = 1;
	return (1);
}

int	update_existing_key(t_exec_data *data, t_env *new_key)
{
	t_list	*head;
	t_env	*search;

	head = data->envp;
	while (head)
	{
		search = head->content;
		if (!ft_strncmp(new_key->key, search->key, ft_strlen(new_key->key)
				+ 1))
		{
			gc_free_one(&data->gc_head_env, search->value);
			search->value = gc_strdup(new_key->value, &data->gc_head_env);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void	add_new_key(t_exec_data *data, t_env *new_key)
{
	t_list	*new_env;

	new_env = gc_malloc(sizeof(t_list), &data->gc_head_env);
	if (!new_env)
		return ;
	new_env->content = new_key;
	new_env->next = NULL;
	ft_lstadd_back(&data->envp, new_env);
}

void	process_export_arg(t_exec_data *data, char *arg)
{
	t_env	*new_key;

	new_key = split_env_line_export(arg, &data->gc_head_env);
	if (!new_key)
		return ;
	if (!check_new_key(new_key))
	{
		handle_export_error(new_key, data);
		return ;
	}
	if (update_existing_key(data, new_key))
		return ;
	add_new_key(data, new_key);
}

int	check_new_key(t_env *env)
{
	int	i;

	i = 1;
	if (env->key[0] != '_' && !ft_isalpha(env->key[0]))
		return (0);
	while (env->key[i])
	{
		if (env->key[i] != '_' && !ft_isalnum(env->key[i]))
			return (0);
		i++;
	}
	return (1);
}
