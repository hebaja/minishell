/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rebuild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:00:13 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/23 16:00:14 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	get_rebuilt_cmd_size(t_token *start_token)
{
	int		inverse_flag;
	size_t	size;
	t_token	*curr_token;

	inverse_flag = 0;
	size = 0;
	curr_token = start_token;
	while (curr_token)
	{
		if (is_redirect(curr_token->type)
			&& (curr_token->next && !is_redirect(curr_token->next->type))
			&& (curr_token->next->next
			&& !is_redirect(curr_token->next->next->type)))
		{
			inverse_flag = 1;
			curr_token = curr_token->next->next;
		}
		curr_token = curr_token->next;
		if (inverse_flag)
			size++;
	}
	return (size);
}

t_token	*get_target_token(t_token *start_token)
{
	t_token	*curr_token;
	t_token	*target_token;

	curr_token = start_token;
	target_token = NULL;
	while (curr_token)
	{
		if (is_redirect(curr_token->type)
			&& (curr_token->next && !is_redirect(curr_token->next->type))
			&& (curr_token->next->next
			&& !is_redirect(curr_token->next->next->type)))
		{
			target_token = curr_token->next->next;
			break ;
		}
		curr_token = curr_token->next;
	}
	return (target_token);
}

t_cmd	*cmd_rebuild(t_token *start_token, t_cmd *cmd, char **paths)
{
	t_token	*target_token;
	t_cmd	*new_cmd;
	size_t	size;

	size = 0;
	target_token = get_target_token(start_token);
	if (target_token)
	{
		size = get_rebuilt_cmd_size(start_token);
		if (size == 0)
			return (cmd);
		int	fd_in = cmd->fd_in;
		int	fd_out = cmd->fd_out;
		cmd_lst_clear(&cmd);
		new_cmd = cmd_build(target_token, size, paths);
		if (!new_cmd)
			return (0);
		new_cmd->fd_in = fd_in;
		new_cmd->fd_out = fd_out;
		return (new_cmd);
	}
	return (cmd);
}
