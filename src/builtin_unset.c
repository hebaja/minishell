/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/13 21:25:33 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char *key, char *variable)
{
	return (strcmp(key, variable) == 0);
}


void	ft_list_remove_if(t_env **env, t_token *variable , int (*cmp)())
{
	t_env	*current;
	t_env	*tmp;

	if (!env || !*env || !variable)
		return ;
	current = *env;
	if (cmp(current->key, variable->next->value))
	{
		tmp = current;
		*env = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		ft_list_remove_if(env, variable, cmp);
	}
	else
		ft_list_remove_if(&current->next, variable, cmp);
}

int	check_env_exists(t_env **env, t_token *variable)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (cmp(tmp->key, variable->next->value))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	builtin_unset(t_env **env, t_token *variable)
{

	if (!variable)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	else if (check_env_exists(env, variable))
	{
		ft_printf("[ERROR]: Environment variable not found\n");
		return ;
	}
	else
		ft_list_remove_if(env, variable, cmp);	
}
