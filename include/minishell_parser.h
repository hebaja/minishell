/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:47:30 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/23 17:21:48 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "minishell_struct.h"

int		is_metacharacter(char c);
int		is_meta_token(char *value);
int		is_dolar(char *value);
int		is_word_join(char **abs_value, int is_start);
int		is_redirect(t_token_type type);
int		quote_mode(t_token **token_lst, char **value,
			char *quoted_value, char quote);
int		find_dolar_pos(t_token *token_lst);
int		var_mode(t_token **token_lst, char **value, char *value_start);
int		var_mode(t_token **token_lst, char **value, char *value_start);
int		quote_mode(t_token **token_lst, char **value,
			char *quoted_value, char quote);
int		regular_mode(t_token **token_lst, char **value,
			char *value_start, int i);
int		conclude_parser(t_ms *ms);
char	*extract_var_key(t_token *token, int dolar_pos);
char	*get_var_value(t_env *env_lst, char *var_key);
void	var_expansion(t_token **token_lst, t_env *env_lst);
void	join_value(char *key, t_token *token, t_env *env_lst, int dolar_pos);
void	builtin_recheck(t_token *token_lst);
void	quotes_var_expansion(t_token **token_lst, t_env *env_lst);
void	quote_removal(t_token *token_lst);

#endif
