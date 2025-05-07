/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:49:07 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/06 17:16:25 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	create_new_node(t_env *env, char *searchequal, t_token *variable)
{
	t_env	*new_node;
	int		size_key;
	int		size_value;

	size_key = searchequal - variable->value;
	size_value = ft_strlen(variable->value) + size_key;
	new_node =  malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = malloc(size_key + 1);
	new_node->value = malloc(size_value + 1);
	if (!new_node->key || !new_node->value)
		return (NULL);
	ft_strncpy(new_node->key, variable->value, size_key);
	ft_strncpy(new_node->value, variable->value, size_value);
	new_node->key[size_key] = '\0';
	new_node->value[size_value] = '\0';
	new_node->next = NULL;
	ft_lstadd_back_env(&env, new_node);
	return(env);
}

t_env	*add_to_env_not_equal_sign(t_env *env, t_token *variable)
{
	t_env	*new_node;
	int		size_key;

	size_key = ft_strlen(variable->value);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = malloc(sizeof(size_key + 1));
	if (!new_node->key)
		return (NULL);
	ft_strncpy(new_node->key, variable->value, size_key);
	new_node->key[size_key] = '\0';
	new_node->next = NULL;
	ft_lstadd_back_env(&env, new_node);
	return (env);
}

t_env	*add_to_env_list(t_env *env, char *searchequal, t_token *variable)
{
	t_env *new_node;
	t_token	tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, variable->value) == 0)
		{
			ft_printf("[ERROR]: the variable already exists\n");
			return (NULL);
		}
		tmp++;
	}
	if (searchequal)
	{
		new_node = create_new_node(env, searchequal, variable);
		if (!new_node)
			return (NULL);
	}
	else
		new_node = add_to_env_not_equal_sign(env, variable);
	return (new_node);
}

t_token	*create_variable(t_token *current, t_env *env)
{
	char	*searchequal;

	if (current->type != WORD)
		return (NULL);
	searchequal = ft_strchr(current->value, '=');
	head->env = add_to_env_list(env, searchequal, current);
	if (!head->env)
	{
		ft_printf("[ERROR] falied the create in new node\n");
		return (NULL);
	}
	return (head);
}
void	builtin_export(t_token *head, t_env *env)
{
	t_token *current;
	t_token	*export_head;
	t_env	*tmp;

	current = head->next;
	tmp = env;
	
	if (!current || current->type != WORD)
	{
		while (tmp)
		{
			ft_printf("%s=%s\n",tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else
		export_head = create_variable(current, env);
}