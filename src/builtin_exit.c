/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:06:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/21 21:19:18 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_exit(t_token *lst)
{
	if (!lst->next || !lst->next->next)
	{
		ft_printf("exit\n");
		exit(0);
	}
	else if (ft_strcmp(lst->next->value, "$") == 0 && ft_strcmp(lst->next->next->value, "?") == 0 )
	{
		ft_printf("exit\n");
		exit(1);
	}
	else if (ft_strcmp(lst->next->value, "$") != 0 && ft_strcmp(lst->next->next->value, "?") == 0 )
	{
		ft_printf("command found %s%s\n",lst->next->value, lst->next->next->value);
		return ;
	}
	else if (ft_strcmp(lst->next->value, "$") == 0 && ft_strcmp(lst->next->next->value, "?") != 0 )
	{
		ft_printf("command found %s%s\n",lst->next->value, lst->next->next->value);
		return ;
	}
}
