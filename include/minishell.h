/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:56:15 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/03 19:56:19 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

# define TERMINAL_PROMPT "🚀 $: "
# define USER "hebatist"

typedef enum e_token_type
{
	OR,
	AND,
	VAR,
	WORD,
	FLAG,
	PIPE,
	DOLAR,
	APPEND,
	HEREDOC,
	VAR_JOIN,
	WORD_JOIN,
	WILDCARD_SOLO,
	WILDCARD_JOIN,
	BACKGROUND,
	REDIRECT_IN,
	REDIRECT_OUT,
	BUILTIN_CD,
	BUILTIN_ENV,
	BUILTIN_PWD,
	BUILTIN_EXIT,
	BUILTIN_ECHO,
	BUILTIN_UNSET,
	BUILTIN_EXPORT,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

int				token_lst_build(t_token **token_lst, char *value);
int				analyse_token_lst(t_token **tokens_head);
int				is_metacharacter(char c);
int				is_meta_token(char *value);
int				append_token(t_token **token_lst, char **value,
					char *value_start, size_t size);
int				quote_mode(t_token **token_lst, char **value,
					char *quoted_value, char quote);
int				find_dolar_pos(t_token *token_lst);
int				is_dolar(char *value);
int				var_mode(t_token **token_lst, char **value, char *value_start);
int				is_word_join(char **abs_value, int is_start);
void			token_clear(t_token *token);
void			token_lst_clear(t_token **token_lst);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			set_extra_meta_chars(t_token *token, char *value_start,
					char quote, int is_joing);
void			token_lst_iterate(t_token *tokens_lst, void(func)(t_token *));
void			var_expansion(t_token **token_lst);
void			quotes_var_expansion(t_token **token_lst);
void			quote_removal(t_token *token_lst);
size_t			token_lst_size(t_token *token_lst);
t_token			*token_build(char **value, char *value_start,
					size_t size, int is_start);
t_token_type	define_type(char *value, char c, int is_join);
/* DEGUB */
void			print_tokens(t_token *token_lst);
char			*print_token_type(t_token_type type);

#endif
