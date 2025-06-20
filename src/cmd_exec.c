/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:46:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/04 23:46:15 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_unused_fds(t_ms *ms, int fd_input, int fd_output)
{
	t_cmd	*cmd_lst;

	cmd_lst = ms->cmd_lst;
	while (cmd_lst)
	{
		if (cmd_lst->is_piped)
		{
			if (cmd_lst->fds[0] != fd_input && cmd_lst->fds[0]
				!= fd_output && cmd_lst->fds[0] > 2)
				close(cmd_lst->fds[0]);
			if (cmd_lst->fds[1] != fd_input && cmd_lst->fds[1]
				!= fd_output && cmd_lst->fds[1] > 2)
				close(cmd_lst->fds[1]);
		}
		cmd_lst = cmd_lst->next;
	}
}

void	exec_child(t_ms *ms, t_cmd *cmd_lst, int fd_input, int fd_output)
{
	char	**envp;

	envp = split_env(ms->env_lst);
	if (fd_input != STDIN_FILENO)
	{
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
	}
	if (fd_output != STDOUT_FILENO)
	{
		dup2(fd_output, STDOUT_FILENO);
		close(fd_output);
	}
	if (is_builtin(cmd_lst->main_type))
		exec_child_builtin(ms, cmd_lst, envp);
	else
		exec_child_execve(ms, cmd_lst, envp);
}

void	set_child_exec_mode(t_ms *ms, t_cmd *cmd_lst)
{
	if (cmd_lst->is_single)
		exec_child(ms, cmd_lst, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd_lst->is_piped && cmd_lst->is_end)
	{
		close_unused_fds(ms, cmd_lst->fds[0], STDOUT_FILENO);
		exec_child(ms, cmd_lst, cmd_lst->fds[0], STDOUT_FILENO);
	}
	else if (cmd_lst->is_piped)
	{
		close_unused_fds(ms, cmd_lst->fds[0], cmd_lst->next->fds[1]);
		exec_child(ms, cmd_lst, cmd_lst->fds[0], cmd_lst->next->fds[1]);
	}
	else
	{
		close_unused_fds(ms, STDIN_FILENO, cmd_lst->next->fds[1]);
		exec_child(ms, cmd_lst, STDIN_FILENO, cmd_lst->next->fds[1]);
	}
}

int	prep_child_exec(t_ms *ms, t_cmd *cmd_lst)
{
	int		pid;

	signal(SIGINT, handle_child_sigint);
	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork processes");
		return (0);
	}
	if (pid == 0)
		set_child_exec_mode(ms, cmd_lst);
	cmd_lst->pid = pid;
	return (1);
}

void	exec_cmd(t_ms *ms)
{
	t_cmd	*cmd_curr;

	cmd_curr = ms->cmd_lst;
	if (!cmd_curr->next && is_builtin(cmd_curr->main_type))
	{
		ms->status = exec_builtin(cmd_curr, ms);
		if (cmd_curr->main_type == BUILTIN_EXIT)
			ms->is_exit = 1;
		return ;
	}
	if (cmd_curr->main_type == HEREDOC)
	{
		close(cmd_curr->fd_in);
		return ;
	}
	while (cmd_curr)
	{
		prep_child_exec(ms, cmd_curr);
		cmd_curr = cmd_curr->next;
	}
	close_fds_parent(ms);
	wait_for_pids(ms);
	signal(SIGINT, handle_sigint);
}
