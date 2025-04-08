/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:32:10 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/07 22:07:07 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void fn_echo(t_token *token_lst)
{
	t_token *current;
	
	if (!token_lst || !token_lst->next)
	{
		ft_printf("\n");
		return ;
	}
	current = token_lst->next;
	while (current)
	{
		if (ft_strcmp(current->value, "-n") == 0)
		{	
			if (!current->next || !current)
				return ;
			else if (current->next->type == WORD)
			{
				ft_printf("%s",current->next->value);
				return ;
			}
		}
		else if (current->type == WORD)
			ft_printf("%s\n", current->value);
		current = current->next;
	}
}


