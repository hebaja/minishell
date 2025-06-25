/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:47:15 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 16:47:16 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell_struct.h"

int		pipe_fds(t_cmd *cmd);
void	redirect(t_token *token_lst);
void	handle_sigint(int sig);
void	handle_child_sigint(int sig);
void	handle_heredoc_sigint(int sig);
void	close_redirect_all_fds(t_cmd *cmd_lst);
void	wait_for_pids(t_ms *ms);
void	close_fds_parent(t_ms *ms);
void	exec_child_builtin(t_ms *ms, t_cmd *cmd, char **envp);
void	exec_child_execve(t_ms *ms, t_cmd *cmd, char **envp);

#endif
