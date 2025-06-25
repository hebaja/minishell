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
	t_token	*curr_token;
	size_t	i;
	t_cmd	*cmd;
	int		offset;

	i = 0;
	offset = 0;
	curr_token = start_token;
	while (i < cmd_size && curr_token)
	{
		if (is_redirect(curr_token->type) && curr_token->next)
			offset += 2;
		curr_token = curr_token->next;
		i++;
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = split_token_value(start_token, cmd_size - offset);
	cmd->main_type = start_token->type;
	cmd->path = set_path(start_token, paths);
	cmd->pid = 0;
	cmd->next = NULL;
	return (cmd);
}

int	add_cmd(t_ms *ms, t_token *start_token, size_t cmd_size)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	new_cmd = cmd_build(start_token, cmd_size, ms->paths);
	if (!new_cmd)
		return (0);
	if (ms->cmd_lst == NULL)
		ms->cmd_lst = new_cmd;
	else
		cmd_lst_add_back(&ms->cmd_lst, new_cmd);
	if (!cmd_build_redirect(ms, start_token, cmd_size))
	{
		cmd_lst_clear(&ms->cmd_lst);
		return (0);
	}
	last_cmd = cmd_lst_last(ms->cmd_lst);
	if (is_redirect(last_cmd->main_type))
	{
		if (!cmd_rebuild(ms, start_token, ms->paths))
			return (0);
	}
	return (1);
}

int	st_md_cmd(t_cmd **cmd_lst, int pipe_flag)
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

int	end_cmd(t_cmd **cmd_lst, int pipe_flag)
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

int	cmd_lst_build(t_ms *ms)
{
	t_token	*st_token;
	t_token	*current_token;
	int		size;
	int		piped;

	st_token = ms->token_lst;
	current_token = ms->token_lst;
	size = 0;
	piped = 0;
	while (current_token)
	{
		if (current_token->type == PIPE && current_token->next)
		{
			if (!add_cmd(ms, st_token, size) || !st_md_cmd(&ms->cmd_lst, piped))
				return (0);
			st_token = current_token->next;
			size = -1;
			piped = 1;
		}
		current_token = current_token->next;
		size++;
	}
	if (!add_cmd(ms, st_token, size) || !end_cmd(&ms->cmd_lst, piped))
		return (0);
	return (1);
}
