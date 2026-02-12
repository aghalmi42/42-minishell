/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:33:14 by alex              #+#    #+#             */
/*   Updated: 2026/02/12 05:16:41 by amoderan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* passe l'environnement en listes chainées pour permettre de coder et d'executer plus facilement unset et export*/

t_list	*envp_to_lst(char **envp)
{
	t_list	*env;
	int		i;
	t_list	*dummy;
	t_env	*content;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		content = split_env_line(envp[i]);
		if (!content)
			return (ft_lstclear(&env, del_env), NULL);
		dummy = ft_lstnew(content);
		if(!dummy)
			return (del_env(content), ft_lstclear(&env, del_env), NULL);
		ft_lstadd_back(&env, dummy);
		i++;
	}
	return (env);
}

/* fais la séparation du egale pour chaque variable du env */

t_env *split_env_line(char *str)
{
	t_env	*node;
	char	*equal_sign;

	node = malloc(sizeof(t_env));
	if (!node)
	return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		node->key = ft_substr(str, 0, equal_sign - str);
		node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		node->key = ft_strdup(str);
		node->value = NULL;
	}
	return (node);
}

/* free le content de chaque noeud de env */

void	del_env(void	*content)
{
	t_env *dummy;

	if (!content)
		return ;
	dummy = (t_env*)content;
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