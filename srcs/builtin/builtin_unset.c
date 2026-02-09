/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:15:45 by alex              #+#    #+#             */
/*   Updated: 2026/02/09 08:00:09 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_unset(t_exec_data *data, t_node *node)
{
	t_list	*curr;
	t_env	*env;
	t_list	*prev;
	int		i;

	i = 1;
	if (!data->envp)
		return ;
	while (node->av[i])
	{
		if (!check_new_unset(node->av[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(node->av[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
			i++;
			continue ;
		}
		prev = NULL;
		curr = data->envp;
		while (curr)
		{
			env = curr->content;
			if (!ft_strncmp(env->key, node->av[i], ft_strlen(node->av[i]) + 1))
			{
				if (prev == NULL)
					data->envp = curr->next;
				else
					prev->next = curr->next;
				ft_lstdelone(curr, del_env);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
}

int	check_new_unset(char *env)
{
	int	i;

	i = 1;
	if (env[0] != '_' && !ft_isalpha(env[0]))
		return (0);
	while(env[i])
	{
		if (env[i] != '_' && !ft_isalnum(env[i]))
			return (0);
		i++;
	}
	return (1);
}
