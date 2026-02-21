/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:18:53 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:18:55 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_env(t_exec_data *data, t_node *node, int export)
{
	t_list	*dummy;
	t_env	*e;

	dummy = data->envp;
	if (node->av[1])
	{
		data->status = 1;
		return (ft_putendl_fd("minishell: env: too many arguments", 2));
	}
	if (export)
		print_export(data);
	else
	{
		while (dummy)
		{
			e = dummy->content;
			printf("%s=%s\n", e->key, e->value);
			dummy = dummy->next;
		}
	}
}

int	compare_keys(t_env *e1, t_env *e2)
{
	return (ft_strncmp(e1->key, e2->key, ft_strlen(e1->key) + 1));
}

void	sort_env_selection(t_list *lst)
{
	t_list	*i;
	t_list	*j;
	t_list	*min_node;
	void	*tmp_content;

	i = lst;
	while (i && i->next)
	{
		min_node = i;
		j = i->next;
		while (j)
		{
			if (compare_keys(j->content, min_node->content) < 0)
				min_node = j;
			j = j->next;
		}
		if (min_node != i)
		{
			tmp_content = i->content;
			i->content = min_node->content;
			min_node->content = tmp_content;
		}
		i = i->next;
	}
}

void	free_copy_list(t_list *copy)
{
	t_list	*tmp;

	while (copy)
	{
		tmp = copy->next;
		free(copy);
		copy = tmp;
	}
}

t_env	*dup_env(t_env *content, t_exec_data *data)
{
	t_env	*dup;
	char	*key;
	char	*value;

	dup = gc_malloc(sizeof(t_env), &data->gc_head_cmd);
	if (!dup)
		return (NULL);
	key = gc_strdup(content->key, &data->gc_head_cmd);
	if (!key)
		return (NULL);
	value = gc_strdup(content->value, &data->gc_head_cmd);
	return (NULL);
	dup->key = key;
	dup->value = value;
	return (dup);
}
