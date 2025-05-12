/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/12 19:12:44 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_env(t_env *env, t_token *variable)
{
	
}

int	check_env_exists(t_env *env, t_token *variable)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key == variable->value)
			return (EXIT_SUCCESS);
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

void	builtin_unset(t_env *env, t_token *variable)
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
		remove_env(env, variable);	
}
