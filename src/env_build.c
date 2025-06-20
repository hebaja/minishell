/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:27:27 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/19 20:35:05 by hebatist         ###   ########.fr       */
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

t_env	*extract_key_and_value(char **envp, char *search_eq, t_env *env_head)
{
	t_env	*new_node;
	int		size_key;
	int		size_value;

	size_key = search_eq - *envp;
	size_value = ft_strlen(*envp) + size_key;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = malloc(size_key + 1);
	new_node->value = malloc(size_value + 1);
	new_node->printed = 0;
	if (!new_node->key || !new_node->value)
		return (NULL);
	ft_strlcpy(new_node->key, *envp, size_key + 1);
	ft_strlcpy(new_node->value, (*envp + size_key + 1), size_value);
	new_node->key[size_key] = '\0';
	new_node->value[size_value] = '\0';
	new_node->next = NULL;
	ft_lstadd_back_env(&env_head, new_node);
	return (env_head);
}

t_env	*save_env_keys_and_values(char **envp)
{
	t_env	*env_head;
	char	*search_equal;

	env_head = NULL;
	while (*envp)
	{
		search_equal = ft_strchr(*envp, '=');
		if (search_equal)
		{
			env_head = extract_key_and_value(envp, search_equal, env_head);
			if (!env_head)
			{
				while (env_head)
					env_head = env_head->next;
			}
		}
		envp++;
	}
	return (env_head);
}

t_env	*build_env_lst(int argc, char **argv, char **envp)
{
	t_env	*env_head;

	(void)argc;
	(void)argv;
	env_head = save_env_keys_and_values(envp);
	return (env_head);
}
