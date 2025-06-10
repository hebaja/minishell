/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:46:04 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/04 23:46:07 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*cmd_build(t_token *start_token, size_t cmd_size, char **paths)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = split_token_value(start_token, cmd_size);
	cmd->path = set_path(start_token, paths);
	cmd->main_type = start_token->type;
	cmd->next = NULL;
	return (cmd);
}

int	append_cmd(t_ms *ms, t_token *start_token, size_t cmd_size)
{
	t_cmd	*new_cmd;

	if (ms->cmd_lst == NULL)
	{
		new_cmd = cmd_build(start_token, cmd_size, ms->paths);
		if (!new_cmd)
			return (0);
		ms->cmd_lst = new_cmd;
	}
	else
	{
		new_cmd = cmd_build(start_token, cmd_size, ms->paths);
		if (!new_cmd)
			return (0);
		cmd_lst_add_back(&ms->cmd_lst, new_cmd);
	}
	return (1);
}

int	set_start_middle_cmd_attrs(t_cmd **cmd_lst, int pipe_flag)
{
	t_cmd	*current_cmd;

	current_cmd = cmd_lst_last(*cmd_lst);
	if (pipe_flag)
	{
		if (!pipe_fds(current_cmd))
			return (0);
	}
	else
		current_cmd->is_piped = 0;
	current_cmd->is_single = 0;
	current_cmd->is_end = 0;
	return (1);
}

int	set_end_cmd_attrs(t_cmd **cmd_lst, int pipe_flag)
{
	t_cmd	*current_cmd;

	current_cmd = cmd_lst_last(*cmd_lst);
	if (pipe_flag)
	{
		if (!pipe_fds(current_cmd))
			return (0);
		current_cmd->is_single = 0;
		current_cmd->is_piped = 1;
	}
	else
	{
		current_cmd->is_single = 1;
		current_cmd->is_piped = 0;
	}
	current_cmd->is_end = 1;
	return (1);
}

int	cmd_lst_build(t_ms *ms, t_token *token_lst)
{
	t_token	*start_token;
	int		cmd_size;
	int		pipe_flag;

	start_token = token_lst;
	cmd_size = 0;
	pipe_flag = 0;
	while (token_lst)
	{
		if (token_lst->type == PIPE)
		{
			if(!append_cmd(ms, start_token, cmd_size)
				|| !set_start_middle_cmd_attrs(&ms->cmd_lst, pipe_flag))
				return (0);
			start_token = token_lst->next;
			cmd_size = -1;
			pipe_flag = 1;
		}
		token_lst = token_lst->next;
		cmd_size++;
	}
	if(!append_cmd(ms, start_token, cmd_size) || 
		!set_end_cmd_attrs(&ms->cmd_lst, pipe_flag))
		return (0);
	// print_cmd_lst(ms->cmd_lst);
	return (1);
}
