/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/26 18:48:33 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var_and_get_value(t_env *env_lst, char *var_key)
{
	while (env_lst)
	{
		if (compare(env_lst->key, var_key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	builtin_unset(t_token *token_lst, t_env **env_lst)
{
	if (!token_lst)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	else if (find_var_and_get_value(*env_lst, token_lst->next->value) == NULL)
	{
		ft_printf("[ERROR]: Environment variable not found\n");
		return ;
	}
	else
		env_lst_remove_if(env_lst, token_lst, compare);
}
