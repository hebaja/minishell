/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:47:41 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 16:47:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include "minishell_includes.h"
# include "minishell_struct.h"

int				token_lst_build(t_ms *ms);
int				analyse_token_lst(t_ms *ms);
int				token_lst_iterate_check(t_token *token_lst,
					int (*func)(t_token *));
int				append_token(t_token **token_lst, char **value,
					char *value_start, size_t size);
void			token_clear(t_token *token);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			token_lst_iterate(t_token *token_lst, void (*func)(t_token *));
void			token_lst_env_iterate(t_token *token_lst, t_env *env_lst,
					void (*func)(t_token *, t_env *));
void			token_lst_join_remove(t_token **token_lst);
void			token_joining(t_token **token_lst);
void			token_lst_clear(t_token **token_lst);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			set_extra_meta_chars(t_token *token,
					char *value_start, char quote);
size_t			token_lst_size(t_token *token_lst);
size_t			token_lst_size(t_token *token_lst);
t_token			*token_build(char **value, char *value_start,
					size_t size, int is_start);
t_token_type	define_type(char *value, char c);

#endif
