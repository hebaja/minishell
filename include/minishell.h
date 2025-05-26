/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:56:15 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/21 20:54:27 by alda-sil         ###   ########.fr       */
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
	struct s_token	*next;
}	t_token;



int				token_lst_build(t_token **tokens_head, char *value);
int				token_lst_perform(t_token **tokens_head);
int				is_metacharacter(char c);
int				is_meta_token(char *value);
int				append_token(t_token **token_lst, char **value,
					char *value_start, size_t size);
int				quote_mode(t_token **token_lst, char **value,
					char *quoted_value, char quote);
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
t_token			*token_build(char **value, char *value_start, size_t size);

#endif
