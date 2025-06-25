/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:56:20 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 19:57:14 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_child_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sig_exit_status(130);
}

int	sig_exit_status(int status)
{
	static int	status_exit = -1;
	int			tmp;

	if (status != -1)
	{
		status_exit = status;
		return (0);
	}
	tmp = status_exit;
	status_exit = -1;
	return (tmp);
}

void	print_permission_denied_msg(t_ms *ms, t_cmd *cmd)
{
	ms->status = 126;
	perror(cmd->path);
}
