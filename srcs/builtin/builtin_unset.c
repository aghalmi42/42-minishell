/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:15:45 by alex              #+#    #+#             */
/*   Updated: 2026/02/05 06:16:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_unset(t_exec_data *data, t_node *node)
{
	t_list	*curr;
	t_env	*env;
	t_list	*prev;
	char	*name;

	name = node->av[1];
	if (!data->envp || !name)
		return ;
	prev = NULL;
	curr = data->envp;
	while (curr)
	{
		env = curr->content;
		if (!ft_strncmp(env->key, name, ft_strlen(name) + 1))
		{
			if (prev == NULL)
				data->envp = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, del_env);
			return ;
		}
		prev = curr;
		curr = curr->next;
		
	}
}