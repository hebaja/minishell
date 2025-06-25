/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:56:15 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/26 19:19:41 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_includes.h"
# include "minishell_redirect.h"
# include "minishell_builtin.h"
# include "minishell_struct.h"
# include "minishell_parser.h"
# include "minishell_token.h"
# include "minishell_exec.h"
# include "minishell_cmd.h"
# include "minishell_env.h"

# define TERMINAL_PROMPT "🚀 $: "
# define BUILTIN_ERROR_STATUS 1
# define BUILTIN_SUCCESS_STATUS 0

int		cmp_token_type(t_token_type a, t_token_type b);
int		cmp_key_str(char *key, char *variable);
int		run_minishell(t_ms *ms);
int		sig_exit_status(int status);
char	**split_token_value(t_token *token_lst, size_t cmd_size);
char	**split_path(t_ms *ms);
void	init_ms(t_ms **ms, int argc, char **argv, char **envp);
void	clean_prompt(t_ms *ms);
void	clean_all(t_ms *ms);
void	clean_matrix(char ***paths);
/* DEGUB */
void	print_tokens(t_token *token_lst);
char	*print_token_type(t_token_type type);
void	print_cmd(t_cmd *cmd_lst);
void	print_cmd_lst(t_cmd *cmd_lst);

#endif
