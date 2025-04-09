/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:56:15 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/08 21:39:42 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "../libft/include/libft.h"

#define TERMINAL_PROMPT "<Pinguimshell>$: "

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
	COMMAND,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

int		token_lst_build(t_token **tokens_head, char *value);
void	token_lst_clear(t_token **token_lst_head);
void	token_lst_add_back(t_token **token_lst_head, t_token *token);
size_t	token_lst_size(t_token *token_lst);
void	builts(t_token *token_lst);
void 	fn_echo(t_token *token_lst);
/* DEGUB */
void	print_tokens(t_token *tokens_head);
char	*print_token_type(t_token_type type);
