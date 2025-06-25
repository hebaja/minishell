/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:21:00 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 20:21:04 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_path(t_ms *ms, char *value)
{
	char	*message;

	if (*value == '/' || ft_strnstr(value, "./", 2))
		return (1);
	message = ft_strjoin(value, ": command not found");
	ft_putendl_fd(message, 2);
	free(message);
	ms->status = 127;
	return (0);
}

void	close_fds_parent(t_ms *ms)
{
	t_cmd	*cmd_curr;

	cmd_curr = ms->cmd_lst;
	while (cmd_curr)
	{
		if (cmd_curr->fd_out > 2)
			close(cmd_curr->fd_out);
		if (cmd_curr->fd_in > 2)
			close(cmd_curr->fd_in);
		if (cmd_curr->is_piped)
		{
			close(cmd_curr->fds[0]);
			close(cmd_curr->fds[1]);
		}
		cmd_curr = cmd_curr->next;
	}
}

void	close_redirect_all_fds(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		if (cmd_lst->fd_out > 2)
			close(cmd_lst->fd_out);
		if (cmd_lst->fd_in > 2)
			close(cmd_lst->fd_in);
		cmd_lst = cmd_lst->next;
	}
}

void	exec_child_builtin(t_ms *ms, t_cmd *cmd, char **envp)
{
	exec_builtin(cmd, ms);
	close_redirect_all_fds(ms->cmd_lst);
	clean_all(ms);
	clean_matrix(&envp);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	exit(EXIT_SUCCESS);
}

void	exec_child_execve(t_ms *ms, t_cmd *cmd, char **envp)
{
	if (cmd->fd_in > 2)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out > 2)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	close_redirect_all_fds(ms->cmd_lst);
	execve(cmd->path, cmd->args, envp);
	close(cmd->fd_in);
	close(cmd->fd_out);
	clean_all(ms);
	clean_matrix(&envp);
	exit(127);
}
