/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:49:07 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/02 18:54:39 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_new_node(t_env *env, char *searchequal, t_token *variable)
{
	t_env	*new_node;
	int		size_key;
	int		size_value;

	size_key = searchequal - variable->value;
	size_value = ft_strlen(variable->value) - size_key;
	new_node =  malloc(sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE) ;
	new_node->key = malloc(size_key + 1);
	new_node->value = malloc(size_value + 1);
	if (!new_node->key || !new_node->value)
		return (EXIT_FAILURE);
	ft_strncpy(new_node->key, variable->value, size_key);
	ft_strncpy(new_node->value, searchequal + 1, size_value);
	new_node->key[size_key] = '\0';
	new_node->value[size_value] = '\0';
	new_node->printed = 0;
	new_node->next = NULL;
	ft_lstadd_back_env(&env, new_node);
	return (EXIT_SUCCESS);
}

int	add_to_env_list(t_env *env, char *searchequal, t_token *variable)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (comper(tmp->key, variable->value))
		{
			ft_printf("[ERROR]: the variable already exists\n");
			return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	if (searchequal)
	{
	
		if (create_new_node(env, searchequal, variable))
		{
			ft_printf("[Error]: The new_node failed\n");	
			return (EXIT_FAILURE);
		}
	}
	else
		ft_printf("\n");
	return (EXIT_SUCCESS);
}

int	create_variable(t_token *current, t_env *env)
{
	char	*searchequal;

	if (current->type != WORD)
	{	
		ft_printf("[Error]: Word not found\n");
		return (EXIT_FAILURE);
	}
	searchequal = ft_strchr(current->value, '=');
	if (add_to_env_list(env, searchequal, current))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_token *head, t_env *env)
{
	t_token *current;
	t_env	*tmp;

	current = head->next;
	tmp = env;
	if (!current || current->type != WORD)
	{
		ft_printed(tmp);
		return (0);
	}	
	else if (create_variable(current, env))
		return (1);
	return (0);
}
