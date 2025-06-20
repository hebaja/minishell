/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:46:56 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 16:46:58 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CMD_H
# define MINISHELL_CMD_H

# include "minishell_includes.h"
# include "minishell_struct.h"

int		cmd_lst_build(t_ms *ms);
int		valid_abs_path(char *abs_pth);
char	*set_path(t_token *token_lst, char **paths);
void	exec_cmd(t_ms *ms);
void	cmd_lst_clear(t_cmd **cmd_lst);
void	cmd_lst_add_back(t_cmd **cmd_lst, t_cmd *cmd);
void	cmd_lst_iterate(t_cmd *cmd_lst,	void (*func)(t_cmd *));
void	cmd_build_redirect(t_ms *ms, t_cmd *cmd, t_token *start_token,
			size_t cmd_size);
t_cmd	*cmd_lst_last(t_cmd *cmd_lst);

#endif
