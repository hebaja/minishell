/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:46:50 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 16:46:52 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

# include "minishell_struct.h"

int	define_type_builtin(char *value, t_token_type *type);
int	exec_builtin(t_cmd *cmd_lst, t_ms *ms);
int	is_builtin(t_token_type type);
int	builtin_cd(t_cmd *cmd_lst, t_env *env_lst);
int	builtin_echo(t_cmd *cmd_lst);
int	builtin_env(t_env *env_lst, t_cmd *cmd);
int	builtin_pwd(t_cmd *cmd_lst);
int	builtin_export(t_cmd *cmd_lst, t_env *env_lst);
int	builtin_unset(t_cmd *cmd_lst, t_env **env_lst);
int	builtin_exit(t_cmd *cmd_lst, int curr_status);
int	update_env_lst(char *value, t_env *env_lst);

#endif
