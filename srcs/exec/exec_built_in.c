/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 03:32:31 by amoderan          #+#    #+#             */
/*   Updated: 2026/02/05 05:45:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	built_in_env(t_exec_data *data, int export)
{
	t_list  *dummy;
	t_env   *e;
	
	dummy = data->envp;
	while(dummy)
	{
		e = dummy->content;
		if (e->value)
			print_env(e, export);
		dummy = dummy->next;
	}
}

void	print_env(t_env *e, int export)
{
	if (export)
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(e->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(e->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(e->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(e->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	built_in_export(t_exec_data *data, t_node *node)
{
	t_list	*head;
	t_list	*new_env;
	t_env	*new_key;
	t_env	*search;

	if (!node->av[1])
		return (built_in_env(data, 1));
	head = data->envp;
	new_key = split_env_line(node->av[1]);
	//printf("%s ", new_key->value);
	if (!new_key)
		return ;
	if (!check_new_key(new_key))
		return (perror("not and identifier"), free(new_key));
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

void	built_in_unset(t_exec_data *data, t_node *node)
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

void	built_in_exit(t_exec_data *data, t_node *node)
{
	int		i;
	char	*number;
	int		cpt;
	
	cpt = 0;
	while(node->av[cpt])
		cpt++;
	if (cpt > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->status = 1;
		return ;
	}
	if (cpt == 1)
		exit(data->status);
	i = 0;
	number = node->av[1];
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		exit(255);
	while(number[i])
	{
		if (!ft_isdigit(number[i]))
			exit(255);
		i++;
	}
	exit(ft_atoi(number));
}