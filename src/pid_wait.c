/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:52:17 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/24 15:52:21 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_not_found_msg(t_ms *ms, char *command)
{
	char	*message;

	ms->status = WEXITSTATUS(ms->status);
	if (ms->status == 127)
	{
		message = ft_strjoin(command, ": command not found");
		ft_putendl_fd(message, 2);
		free(message);
	}
}

void	wait_for_pids(t_ms *ms)
{
	t_cmd	*cmd_curr;

	cmd_curr = ms->cmd_lst;
	while (cmd_curr)
	{
		if (cmd_curr->pid)
		{
			waitpid(cmd_curr->pid, &ms->status, 0);
			if (WIFEXITED(ms->status))
			{
				if (WEXITSTATUS(ms->status))
					command_not_found_msg(ms, cmd_curr->path);
			}
		}
		cmd_curr = cmd_curr->next;
	}
}
