/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:50:58 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 19:51:00 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	deal_redirect(t_cmd *cmd_curr)
{
	if (is_redirect(cmd_curr->main_type))
	{
		if (cmd_curr->main_type == REDIRECT_IN
			|| cmd_curr->main_type == HEREDOC)
			close(cmd_curr->fd_in);
		if (cmd_curr->main_type == REDIRECT_OUT
			|| cmd_curr->main_type == APPEND)
			close(cmd_curr->fd_out);
		return (1);
	}
	return (0);
}

int	set_redirect(t_ms *ms, t_token *curr_token, int *tmp_fd_out,
		int *tmp_fd_in)
{
	int	res;

	res = 0;
	if (curr_token->next && (curr_token->type == REDIRECT_IN
			|| curr_token->type == HEREDOC))
		res = set_redirect_in(ms, curr_token, tmp_fd_in);
	if (curr_token->next && (curr_token->type == REDIRECT_OUT
			|| curr_token->type == APPEND))
		res = set_redirect_out(tmp_fd_out, curr_token);
	return (res);
}

void	attribuite_cmd_fds(int fd_in, int fd_out, t_cmd *cmd)
{
	if (fd_in > -1)
		cmd->fd_in = fd_in;
	if (fd_out > -1)
		cmd->fd_out = fd_out;
}

int	cmd_build_redirect(t_ms *ms, t_token *start_token,
		size_t cmd_size)
{
	int		res;
	int		tmp_fd_in;
	int		tmp_fd_out;
	t_token	*curr_token;
	t_cmd	*last_cmd;

	res = 0;
	tmp_fd_in = -1;
	tmp_fd_out = -1;
	last_cmd = cmd_lst_last(ms->cmd_lst);
	last_cmd->fd_out = STDOUT_FILENO;
	last_cmd->fd_in = STDIN_FILENO;
	curr_token = start_token;
	while (cmd_size && curr_token)
	{
		res = set_redirect(ms, curr_token, &tmp_fd_out, &tmp_fd_in);
		if (res < 0)
			return (0);
		cmd_size--;
		curr_token = curr_token->next;
	}
	attribuite_cmd_fds(tmp_fd_in, tmp_fd_out, last_cmd);
	return (1);
}
