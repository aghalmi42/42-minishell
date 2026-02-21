/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:26:30 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/20 09:27:26 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*envp_to_lst(char **envp, t_list **gc_head_env)
{
	t_list	*env;
	int		i;
	t_list	*dummy;
	t_env	*content;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		content = split_env_line(envp[i], gc_head_env);
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

/* fais la séparation du egale pour chaque variable du env */
t_env	*split_env_line(char *str, t_list **gc_head_env)
{
	t_env	*node;
	char	*equal_sign;

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

/* free le content de chaque noeud de env */
void	del_env(void	*content)
{
	t_env	*dummy;

	if (!content)
		return ;
	dummy = (t_env *)content;
	if (dummy->key)
		free(dummy->key);
	if (dummy->value)
		free(dummy->value);
	free(dummy);
}

void	free_envp(t_exec_data *data)
{
	t_list	*cur;
	t_list	*next;

	cur = data->envp;
	next = NULL;
	while (cur)
	{
		next = cur->next;
		ft_lstdelone(cur, del_env);
		cur = next;
	}
}
