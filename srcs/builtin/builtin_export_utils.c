
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
		if (!ft_strncmp(new_key->key, search->key,
				ft_strlen(new_key->key) + 1))
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
	// printf("key : %s \'%c\' value : %s\n", new_key->key,new_key->key[0], new_key->value);
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
	while(env->key[i])
	{
		if (env->key[i] != '_' && !ft_isalnum(env->key[i]))
			return (0);
		i++;
	}
	return (1);
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
		if(!dummy)
			return (NULL);
		dummy->content = content;
		dummy->next = NULL;
		ft_lstadd_back(&env, dummy);
		i++;
	}
	return (env);

}

t_env *split_env_line_export(char *str, t_list **gc_head_env)
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
		if(!node->key)
			return (NULL);
		node->value = NULL;
	}
	return (node);
}