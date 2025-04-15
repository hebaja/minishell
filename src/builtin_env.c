/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:05:22 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/15 20:50:56 by alda-sil         ###   ########.fr       */
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

void	save_env_keys(char **envp)
{
	t_env 	*env_head;
	t_env	*new_node;
	char	*searchequal;
	int		size_key;
	
	env_head = NULL;
	while (*envp)
	{
		searchequal = ft_strchr(*envp, '=');
		if (searchequal)
		{
			size_key = searchequal - *envp;
			new_node = malloc(sizeof(t_env));
			if (!new_node)
				return ;
			new_node->key = malloc(size_key + 1);
			if (!new_node->key)
			{
				free(new_node);
				return ;
			}
			ft_strncpy(new_node->key, *envp, size_key);
			new_node->key[size_key] = '\0';
			new_node->next = NULL;
			ft_lstadd_back_env(&env_head, new_node);
		}
		envp++;
	}

}

void	save_env_value(char **envp)
{
	t_env	*env_head;
	t_env	*new_node;
	char	*searchequal;
	int		size_value;

	env_head = NULL;
	while (*envp)
	{
		searchequal	= ft_strchr(*envp, '=');
		if (searchequal)
		{
			searchequal += 1;
			size_value = (ft_strlen(searchequal));
			
		}
		envp++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	save_env_keys(envp);
	save_env_value(envp);
	return (0);
}