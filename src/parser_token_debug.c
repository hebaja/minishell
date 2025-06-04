/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_debug.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:36 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/06 14:29:38 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*print_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == BACKGROUND)
		return ("BACKGROUND");
	if (type == WILDCARD_SOLO)
		return ("WILDCARD_SOLO");
	if (type == WILDCARD_JOIN)
		return ("WILDCARD_JOIN");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == VAR)
		return ("VAR");
	if (type == DOLAR)
		return ("DOLAR");
	if (type == BUILTIN_CD)
		return ("BUILTIN_CD");
	if (type == BUILTIN_ENV)
		return ("BUILTIN_ENV");
	if (type == BUILTIN_PWD)
		return ("BUILTIN_PWD");
	if (type == BUILTIN_EXIT)
		return ("BUILTIN_EXIT");
	if (type == BUILTIN_ECHO)
		return ("BUILTIN_ECHO");
	if (type == BUILTIN_UNSET)
		return ("BUILTIN_UNSET");
	if (type == BUILTIN_EXPORT)
		return ("BUILTIN_EXPORT");
	if (type == SINGLE_QUOTED)
		return ("SINGLE_QUOTED");
	if (type == DOUBLE_QUOTED)
		return ("DOUBLE_QUOTED");
	return ("");
}

void	print(t_token *token_lst)
{
	printf("value = %s, type = %s, join = %d, next = %p\n", 
		token_lst->value,
		print_token_type(token_lst->type),
		token_lst->join,
		token_lst->next);
}

void	print_tokens(t_token *tokens_head)
{
	token_lst_iterate(tokens_head, print);
}
