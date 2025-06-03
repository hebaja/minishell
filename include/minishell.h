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

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

# define TERMINAL_PROMPT "🚀 $: "

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
	t_token_type	type;
	int				join;
	struct s_token	*next;
}	t_token;

int				token_lst_build(t_token **token_lst, char *value);
int				analyse_token_lst(t_token **token_lst, t_env *env_lst);
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
int				check_redirect(t_token *token_lst);
int				token_lst_iterate_check(t_token *token_lst, int (*func)(t_token *));
int				conclude_parser(t_token *token_lst);
void			token_clear(t_token *token);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			set_extra_meta_chars(t_token *token,
				char *value_start, char quote);
void			token_lst_iterate(t_token *token_lst, void (*func)(t_token *));
int				token_lst_iterate_check(t_token *token_lst, int (*func)(t_token *));
void			token_lst_env_iterate(t_token *token_lst, t_env *env_lst, void (*func)(t_token *, t_env *));
void			var_expansion(t_token **token_lst, t_env *env_lst);
void			join_value(char *key, t_token *token, t_env *env_lst, int dolar_pos);
void			quotes_var_expansion(t_token **token_lst, t_env *env_lst);
void			quote_removal(t_token *token_lst);
void			token_lst_join_remove(t_token **token_lst);
void			token_joining(t_token **token_lst);
void			builtin_recheck(t_token *token_lst);
void			iscommandToken(t_token *token_lst, t_env **env);
size_t			token_lst_size(t_token *token_lst);
char			*extract_var_key(t_token *token, int dolar_pos);
t_token			*token_build(char **value, char *value_start,
					size_t size, int is_start);
t_token_type	define_type(char *value, char c);
int     		cmp(t_token_type a, t_token_type b);
void			token_lst_clear(t_token **token_lst);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			builtin_cd(t_token *token_lst, t_env *env_lst);
void			builtin_echo(t_token *token_lst);
t_env			*extract_key_and_value(char **envp, char *searchequal, t_env *env_lst);
t_env 			*build_env_lst(int argc, char **argv, char **envp);
void			print_env_sort(t_env *env_lst);
void			ft_lstadd_back_env(t_env **env_head, t_env *new_node);
void			builtin_env(t_env *env_lst);
void			builtin_pwd(void);
void			builtin_export(t_token *token_lst, t_env *env_lst);
void			builtin_unset(t_token *token_lst, t_env **env_lst);
void			env_lst_remove_if(t_env **env_lst, char *value, int cmp(char *s1, char *s2));
int				builtin_exit(t_token **token_lst, t_env **env_lst);
size_t			token_lst_size(t_token *token_lst);
void			print_tokens(t_token *token_lst);
char			*print_token_type(t_token_type type);
int				compare(char *key, char *variable);
void			env_lst_iterate(t_env *env_lst, void (*f)(t_env *env_lst));
void			env_lst_clear(t_env **env_lst);
char			*get_var_value(t_env *env_lst, char *var_key);
void			update_env_lst(char *value, t_env *env_lst);
/* DEGUB */
void			print_tokens(t_token *token_lst);

#endif
