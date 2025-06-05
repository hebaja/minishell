/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:46:26 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/04 23:46:29 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

 t_cmd	*cmd_lst_last(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		if (cmd_lst->next == NULL)
			break ;
		cmd_lst = cmd_lst->next;
	}
	return (cmd_lst);
}

void	cmd_lst_add_back(t_cmd **cmd_lst, t_cmd *cmd)
{
	if (*cmd_lst == NULL)
		*cmd_lst = cmd;
	else
		cmd_lst_last(*cmd_lst)->next = cmd;
}

void	cmd_clear(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd->args[++i])
		free(cmd->args[i]);
	free(cmd->args);
	cmd->args = NULL;
	free(cmd->path);
	cmd->path = NULL;
	free(cmd);
	cmd = NULL;
}

void	cmd_lst_clear(t_cmd **cmd_lst)
{
	if (cmd_lst != NULL)
		cmd_lst_iterate(*cmd_lst, cmd_clear);
	*cmd_lst = NULL;
}
