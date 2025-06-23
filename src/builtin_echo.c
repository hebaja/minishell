/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:01:01 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/23 16:01:03 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		is_break_line;

	i = 1;
	is_break_line = 1;
	if (!cmd->args[1])
		is_break_line = 1;
	if (cmd->args[0] && (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0))
	{
		is_break_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->fd_out);
		i++;
		if ((cmd->args[i] && is_metacharacter(cmd->args[i][0]))
			|| !cmd->args[i])
			break ;
		ft_putstr_fd(" ", cmd->fd_out);
	}
	if (is_break_line)
		ft_putstr_fd("\n", cmd->fd_out);
	return (BUILTIN_SUCCESS_STATUS);
}
