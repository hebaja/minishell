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


void	builtin_unset(t_token *token_lst, t_env **env_lst)
{
	if (!token_lst)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	else if (get_var_value(*env_lst, token_lst->next->value) == NULL)
	{
		ft_printf("Environment variable not found\n");
		return ;
	}
	else
		env_lst_remove_if(env_lst, token_lst->next->value, compare);
}
