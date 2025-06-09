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
# include <stdlib.h>
# include <sys/wait.h>
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

typedef struct s_cmd
{
	int				fds[2];
	int				is_piped;
	int				is_end;
	int				is_single;
	t_token_type	main_type;
	char			*path;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;
/*
typedef struct s_cmd
{
	int				fd[2];
	t_token			*token_lst;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;
*/

int				token_lst_build(t_token **token_lst, char *value);
int				analyse_token_lst(t_token **token_lst, t_env *env_lst);
int				cmd_lst_build(t_cmd **cmd_lst, t_token *token_lst, char **paths);
int				pipe_fds(t_cmd *cmd);
int				valid_abs_path(char *abs_pth);
char			*set_path(t_token *token_lst, char **paths);
t_cmd			*cmd_lst_last(t_cmd *cmd_lst);
char			*build_env_sp(t_env *env);
char			**split_env(t_env *env_lst);
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
int				exec_builtin(t_cmd *cmd, t_env *env_lst);
int				check_redirect(t_token *token_lst);
int				conclude_parser(t_token *token_lst);
void			exec_cmd(t_cmd *cmd_lst, t_env *env_lst, int *status_ctrl);
void			token_clear(t_token *token);
void			cmd_lst_clear(t_cmd **cmd_lst);
void			token_lst_add_back(t_token **token_lst, t_token *token);
void			cmd_lst_add_back(t_cmd **cmd_lst, t_cmd *cmd);
void			set_extra_meta_chars(t_token *token,
				char *value_start, char quote);
void			token_lst_iterate(t_token *token_lst, void (*func)(t_token *));
char			**split_path(t_env *env_lst);
void			clean_prompt(t_token **token_lst, char **input, t_cmd **cmd_lst,
					char **split_paths);
void			clean_all(t_token **token_lst, char **input, t_cmd **cmd_lst,
					char **split_paths);
void			clean_matrix(char **paths);
int				token_lst_iterate_check(t_token *token_lst, int (*func)(t_token *));
void			token_lst_env_iterate(t_token *token_lst, t_env *env_lst, void (*func)(t_token *, t_env *));
void			cmd_lst_iterate(t_cmd *cmd_lst,	void (*func)(t_cmd *));
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
int				is_builtin(t_token_type type);
int     		cmp(t_token_type a, t_token_type b);
void			token_lst_clear(t_token **token_lst);
void			token_lst_add_back(t_token **token_lst, t_token *token);
int				builtin_cd(t_cmd *cmd_lst, t_env *env_lst);
int				builtin_echo(t_cmd *cmd_lst);
int				builtin_env(t_env *env_lst);
int				builtin_pwd(void);
int				builtin_export(t_cmd *cmd_lst, t_env *env_lst);
int				builtin_unset(t_cmd *cmd_lst, t_env **env_lst);
int				builtin_exit(t_cmd *cmd_lst);
t_env			*extract_key_and_value(char **envp, char *searchequal, t_env *env_lst);
t_env 			*build_env_lst(int argc, char **argv, char **envp);
void			print_env_sort(t_env *env_lst);
void			ft_lstadd_back_env(t_env **env_head, t_env *new_node);
void			env_lst_remove_if(t_env **env_lst, char *value, int cmp(char *s1, char *s2));
size_t			token_lst_size(t_token *token_lst);
void			print_tokens(t_token *token_lst);
char			*print_token_type(t_token_type type);
int				compare(char *key, char *variable);
void			env_lst_iterate(t_env *env_lst, void (*f)(t_env *env_lst));
void			env_lst_clear(t_env **env_lst);
int				env_lst_size(t_env *lst);
char			*get_var_value(t_env *env_lst, char *var_key);
int				update_env_lst(char *value, t_env *env_lst);
char			**split_token_value(t_token *token_lst, size_t cmd_size);
/* DEGUB */
void			print_tokens(t_token *token_lst);
void			print_cmd(t_cmd *cmd_lst);
void			print_cmd_lst(t_cmd *cmd_lst);

#endif
