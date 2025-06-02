/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/02 18:54:28 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_env_exists(t_env **env, t_token *variable)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (comper(tmp->key, variable->next->value))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	builtin_unset(t_env **env, t_token *variable)
{
	if (!variable)
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	else if (check_env_exists(env, variable))
	{
		ft_printf("[ERROR]: Environment variable not found\n");
		return (1);
	}
	else
		ft_list_remove_if(env, variable, comper);
	return (0);
}
