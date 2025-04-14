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

#include <stdio.h>
#include <readline/readline.h>
#include "../libft/include/libft.h"

#define TERMINAL_PROMPT "🚀 $: "

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
	WILDCARD,
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
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

int				token_lst_build(t_token **tokens_head, char *value);
void			token_lst_clear(t_token **token_lst_head);
void			token_lst_add_back(t_token **token_lst_head, t_token *token);
size_t			token_lst_size(t_token *token_lst);
t_token_type	define_type(char *value);
/* DEGUB */
void	print_tokens(t_token *tokens_head);
char	*print_token_type(t_token_type type);
