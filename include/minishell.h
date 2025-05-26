/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:56:15 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/26 17:53:15 by alda-sil         ###   ########.fr       */
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

typedef struct s_env
{
	int				printed;
	char			*value;
	char			*key;
	struct s_env	*next;
} t_env;

typedef struct s_token
{
	char			*value;
	char			*export;
	t_token_type	type;
	int				join;
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
int				var_mode(t_token **token_lst, char **value, char *value_start);
int				quote_mode(t_token **token_lst, char **value,
					char *quoted_value, char quote);
int				regular_mode(t_token **token_lst, char **value, 
					char *value_start, int i);
int				define_type_builtin(char *value, t_token_type *type);
void			conclude_parser(t_token *token_lst);
void			token_clear(t_token *token);
void			token_lst_clear(t_token **token_lst);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			set_extra_meta_chars(t_token *token, char *value_start,
					char quote);
void			token_lst_iterate(t_token *tokens_lst, void(func)(t_token *));
void			var_expansion(t_token **token_lst);
void			quotes_var_expansion(t_token **token_lst);
void			quote_removal(t_token *token_lst);
void			token_lst_join_remove(t_token **token_lst);
void			token_joining(t_token **token_lst);
void			builtin_recheck(t_token *token_lst);
size_t			token_lst_size(t_token *token_lst);
t_token			*token_build(char **value, char *value_start,
					size_t size, int is_start);
t_token_type	define_type(char *value, char c);
/* DEGUB */
void			print_tokens(t_token *token_lst);
int				cmp(char *key, char *variable);
int				ascending(char *a, char *b);
void			token_lst_clear(t_token **token_lst_head);
void			token_lst_add_back(t_token **token_lst_head, t_token *token);
void			set_extra_meta_chars(t_token *token, char *value_start);
void			builtin_cd(t_token *token_lst);
void			builtin_echo(t_token *token_lst);
t_env			*extract_key_and_value(char **envp, char *searchequal, t_env *env_head);
t_env 			*fn_enviroment_variables(char **envp);
void			ft_printed(t_env *lst);
void			ft_lstadd_back_env(t_env **env_head, t_env *new_node);
void			builtin_env(t_env *env_head);
void			builtin_pwd(void);
void			builtin_export(t_token *head, t_env *env);
void			builtin_unset(t_env **env, t_token *variable);
void			ft_list_remove_if(t_env **env, t_token *variable , int (*cmp)());
void			builtin_exit(t_token *lst);
size_t			token_lst_size(t_token *token_lst);
t_token_type	define_type(char *value);
void			print_tokens(t_token *tokens_head);
char			*print_token_type(t_token_type type);

#endif
