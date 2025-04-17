/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:05:22 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/16 21:22:06 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_back_env(t_env **env_head, t_env *new_node)
{
	t_env	*tmp;

	if (!*env_head)
		*env_head = new_node;
	else
	{
		tmp = *env_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_env	*extract_key_value(char **envp, char *searchequal, t_env *env_head)
{
	t_env *new_node;
	int	size_key;
	int	size_value;

	size_key = searchequal - *envp;
	size_value = ft_strlen(*envp) + size_key;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = malloc(size_key + 1);
	new_node->value = malloc(size_value + 1);
	ft_strncpy(new_node->key, *envp, size_key);
	ft_strncpy(new_node->value,  (*envp + size_key + 1), size_value);
	new_node->key[size_key] =  '\0';
	new_node->key[size_value] =  '\0';
	new_node->next = NULL;
	ft_lstadd_back_env(&env_head, new_node);
	return (env_head);
}

t_env	*save_env_keys_and_value(char **envp)
{
	t_env 	*env_head;
	char	*searchequal;
	
	env_head = NULL;
	while (*envp)
	{
		searchequal = ft_strchr(*envp, '=');
		if (searchequal)
		{
			env_head = extract_key_value(envp, searchequal, env_head);
			if (!env_head)
			{
				while(env_head)
				{
					free(env_head);
					env_head = env_head->next;
				}
				return (NULL);
			}
		}
		envp++;
	}

	t_env *tmp = env_head;

	while (tmp)
	{
		ft_printf("%s  \n", tmp->value);
		tmp = tmp->next;
	}
	
	return (env_head);
}

int	main(int argc, char **argv, char **envp)
{
	t_env *env_head;

	env_head = save_env_keys_and_value(envp);
	while(env_head)
	{
		free(env_head);
		env_head = env_head->next;
	}
	return (0);
}