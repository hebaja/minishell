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

int	is_numeric(char *value)
{
	int	i;

	i = -1;
	while (value[++i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
	}
	return (1);
}

/* TODO We need to set $? to make exit work properly */
int	builtin_exit(t_cmd *cmd_lst)
{
	int	exit_value;

	if (cmd_lst->args[1])
	{
		if (!is_numeric(cmd_lst->args[1]))
		{
			ft_printf("exit: %s: numeric argument required\n", 
				cmd_lst->args[1]);
			exit_value = 2;
		}
		else
			exit_value = ft_atoi(cmd_lst->args[1]);
	}
	return (exit_value);
}
