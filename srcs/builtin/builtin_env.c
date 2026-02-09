/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:11:35 by alex              #+#    #+#             */
/*   Updated: 2026/02/09 07:40:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_env(t_exec_data *data,t_node *node, int export)
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
	while(dummy)
	{
		e = dummy->content;
		printf("%s=%s\n",e->key, e->value);
		dummy = dummy->next;
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


void	print_export(t_exec_data *data)
{
	t_list	*copy;
	t_list	*curr;
	t_env	*e;

	copy = NULL;
	curr = data->envp;
	while (curr)
	{
		ft_lstadd_back(&copy, ft_lstnew(curr->content));
		curr = curr->next;
	}
	sort_env_selection(copy);
	curr = copy;
	while (curr)
	{
		e = curr->content;
		printf("export %s=\"%s\"\n",e->key, e->value);
		curr = curr->next;
	}
}

