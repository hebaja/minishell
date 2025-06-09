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

void	close_unused_fds(t_cmd *cmd_lst, int fd_input, int fd_output)
{
	while (cmd_lst)
	{
		if (cmd_lst->is_piped)
		{
			if (cmd_lst->fds[0] != fd_input && cmd_lst->fds[0] != fd_output && cmd_lst->fds[0] > 2)
				close(cmd_lst->fds[0]);
			if (cmd_lst->fds[1] != fd_input && cmd_lst->fds[1] != fd_output && cmd_lst->fds[1] > 2)
				close(cmd_lst->fds[1]);
		}
		cmd_lst = cmd_lst->next;
	}
}

void	exec_child(t_cmd *cmd_lst, t_env *env_lst, int fd_input, int fd_output)
{
	char	**envp;

	envp = split_env(env_lst);
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
	{
		exec_builtin(cmd_lst, env_lst);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(cmd_lst->path, cmd_lst->args, envp);
		exit(EXIT_FAILURE);
	}
}

void	set_child_exec_mode(t_cmd **cmd_head, t_cmd *cmd_lst, t_env *env_lst)
{
	if (cmd_lst->is_single)
		exec_child(cmd_lst, env_lst, STDIN_FILENO, STDOUT_FILENO);
	else if (cmd_lst->is_piped && cmd_lst->is_end)
	{
		close_unused_fds(*cmd_head, cmd_lst->fds[0], STDOUT_FILENO);
		exec_child(cmd_lst, env_lst, cmd_lst->fds[0], STDOUT_FILENO);
	}
	else if (cmd_lst->is_piped)
	{
		close_unused_fds(*cmd_head, cmd_lst->fds[0], cmd_lst->next->fds[1]);
		exec_child(cmd_lst, env_lst, cmd_lst->fds[0], cmd_lst->next->fds[1]);
	}
	else 
	{
		close_unused_fds(*cmd_head, STDIN_FILENO, cmd_lst->next->fds[1]);
		exec_child(cmd_lst, env_lst, STDIN_FILENO , cmd_lst->next->fds[1]);
	}
}

int	prep_child_exec(t_cmd **cmd_head, t_cmd *cmd_lst, t_env *env_lst,
	int *status_ctrl)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork processes");
		return (0);
	}
	if (pid == 0)
		set_child_exec_mode(cmd_head, cmd_lst, env_lst);
	if (cmd_lst->is_piped)
	{
		close(cmd_lst->fds[0]);
		close(cmd_lst->fds[1]);
	}
	waitpid(pid, &status, 0);
	status_ctrl[0] = status;
	return (1);
}

void	exec_cmd(t_cmd *cmd_lst, t_env *env_lst, int *status_ctrl)
{
	t_cmd	**cmd_head;

	if (!cmd_lst->next && is_builtin(cmd_lst->main_type))
	{
		status_ctrl[0] = exec_builtin(cmd_lst, env_lst);
		if (cmd_lst->main_type == BUILTIN_EXIT)
			status_ctrl[1] = 1;
		return ;
	}
	cmd_head = &cmd_lst;
	while (cmd_lst)
	{
		prep_child_exec(cmd_head, cmd_lst, env_lst, status_ctrl);
		cmd_lst = cmd_lst->next;
	}
}
