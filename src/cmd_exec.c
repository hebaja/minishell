/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:46:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/11 21:04:55 by alda-sil         ###   ########.fr       */
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
	{
		exec_builtin(cmd_lst, ms->env_lst);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(cmd_lst->path, cmd_lst->args, envp);
		exit(EXIT_FAILURE);
	}
}

void	set_child_exec_mode(t_ms *ms, t_cmd *cmd_lst, int fd_input, int fd_output) 
{
	if (cmd_lst->is_single)
		exec_child(ms, cmd_lst, fd_input, fd_output);
	
	else if (cmd_lst->is_piped && cmd_lst->is_end && fd_input == STDIN_FILENO && fd_output == STDOUT_FILENO)
	{
		close_unused_fds(ms, cmd_lst->fds[0], STDOUT_FILENO);
		exec_child(ms, cmd_lst, cmd_lst->fds[0], STDOUT_FILENO);
	}
	
	else if (cmd_lst->is_piped && cmd_lst->is_end)
	{
		close_unused_fds(ms, fd_input, STDOUT_FILENO);
		exec_child(ms, cmd_lst, fd_input, STDOUT_FILENO);
	}
	else if (cmd_lst->is_piped)
	{
		close_unused_fds(ms, cmd_lst->fds[0], cmd_lst->fds[1]);
		exec_child(ms, cmd_lst, cmd_lst->fds[0], cmd_lst->fds[1]);
	}
	else if (fd_input == STDIN_FILENO && fd_output == STDOUT_FILENO)
	{
		close_unused_fds(ms, STDIN_FILENO, cmd_lst->fds[1]);
		exec_child(ms, cmd_lst, STDIN_FILENO, cmd_lst->fds[1]);
	}
	else
	{
		close_unused_fds(ms, fd_input, fd_output);
		exec_child(ms, cmd_lst, fd_input , fd_output);
	}
}

void	set_child_exec_redi_mode(t_ms *ms, t_cmd *cmd_lst)
{
	int	fd_in;
	int	fd_out;

	fd_in = ms->token_lst->fd_in;
	fd_out =  ms->token_lst->fd_out;

	if (fd_in != -1 && fd_out != -1)
		set_child_exec_mode(ms, cmd_lst, fd_in, fd_out);
	else if (fd_in != -1 && fd_out == -1)
		set_child_exec_mode(ms, cmd_lst, fd_in, STDOUT_FILENO);
	else if (fd_in == -1 && fd_out != -1)
		set_child_exec_mode(ms, cmd_lst, STDIN_FILENO, fd_out);
	else if (fd_in == -1 && fd_out == -1)
		set_child_exec_mode(ms, cmd_lst, STDIN_FILENO, STDOUT_FILENO);
}


int	prep_child_exec(t_ms *ms, t_cmd *cmd_lst)
{
	int		pid;
	int		status;
	
	ft_signal_exec();
	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork processes");
		return (0);
	}
	if (pid == 0)
		set_child_exec_redi_mode(ms, cmd_lst);
	if (cmd_lst->is_piped)
	{
		close(cmd_lst->fds[0]);
		close(cmd_lst->fds[1]);
	}
	waitpid(pid, &status, 0);
	ms->status = status;
	ft_signal();
	return (1);
}

void	dup_cmd(t_ms *ms, t_cmd *cmd_lst)
{
	int	in_tmp;
	int	out_tmp;

	in_tmp = dup(STDIN_FILENO);
	out_tmp = dup(STDOUT_FILENO);

	if (ms->token_lst->fd_in != STDIN_FILENO)
		dup2(ms->token_lst->fd_in, STDIN_FILENO);
	if (ms->token_lst->fd_out != STDIN_FILENO)
		dup2(ms->token_lst->fd_out, STDOUT_FILENO);
	ms->status = exec_builtin(cmd_lst, ms->env_lst);
	dup2(in_tmp, STDIN_FILENO);
	dup2(out_tmp, STDOUT_FILENO);
	close(in_tmp);
	close(out_tmp);
}


void	exec_cmd(t_ms *ms, t_cmd *cmd_lst)
{
	if (!cmd_lst->next && is_builtin(cmd_lst->main_type))
	{
		dup_cmd(ms, cmd_lst);
		if (cmd_lst->main_type == BUILTIN_EXIT)
			ms->is_exit = 1;
		return ;
	}
	while (cmd_lst)
	{
		prep_child_exec(ms, cmd_lst);
		cmd_lst = cmd_lst->next;
	}
}
