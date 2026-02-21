/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:21:28 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 08:26:45 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_export(t_exec_data *data, t_node *node)
{
	int	i;

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
	i = 1;
	while (node->av[i])
	{
		process_export_arg(data, node->av[i]);
		i++;
	}
}

t_list	*envp_to_lst_export(char **envp, t_list **gc_head_env)
{
	t_list	*env;
	int		i;
	t_list	*dummy;
	t_env	*content;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		content = split_env_line_export(envp[i], gc_head_env);
		if (!content)
			return (NULL);
		dummy = gc_malloc(sizeof(t_list), gc_head_env);
		if (!dummy)
			return (NULL);
		dummy->content = content;
		dummy->next = NULL;
		ft_lstadd_back(&env, dummy);
		i++;
	}
	return (env);
}

t_env	*split_env_line_export(char *str, t_list **gc_head_env)
{
	t_env	*node;
	char	*equal_sign;

	while (*str && *str > 0 && *str < 32)
		str++;
	node = gc_malloc(sizeof(t_env), gc_head_env);
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		node->key = gc_substr(str, 0, equal_sign - str, gc_head_env);
		node->value = gc_strdup(equal_sign + 1, gc_head_env);
		if (!node->value)
			return (NULL);
	}
	else
	{
		node->key = gc_strdup(str, gc_head_env);
		if (!node->key)
			return (NULL);
		node->value = NULL;
	}
	return (node);
}
