/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:30 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/02 19:51:06 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	exit_status(int	status)
{
	static	int	status_exit = 0;
	
	if (status > -1)
		status_exit = status;
	return (status_exit);
}


int	display_output(t_token *current)
{
	if (ft_strcmp(current->value, "-n") == 0)
	{
		while (current->next->type == WORD)
		{
			ft_printf("%s ", current->next->value);
			if (current->next == NULL)
				return (1);
			current = current->next;
		}
	}
	else if (current->type == WORD)
	{
		while (current->value)
		{
			ft_printf("%s ", current->value);
			if (current->next == NULL)
			{
				ft_printf("\n");
				return (1);
			}
			current = current->next;
		}
		return (1);
	}
	return (0);
}

int	builtin_echo(t_token *token_lst)
{
	t_token *current;

	if (!token_lst || !token_lst->next)
	{
		ft_printf("\n");
		return (0);
	}
	current = token_lst->next;
	if (display_output(current))
		return (0);
	else
		ft_printf("\n");
	return (0);
}
