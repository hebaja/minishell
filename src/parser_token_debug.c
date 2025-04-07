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
	if (type == FLAG)
		return "FLAG";
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

void	print_tokens(t_token *tokens_head)
{
	t_token	*current_token;

	current_token = tokens_head;
	while (current_token)
	{
		printf("value = %s, type = %s, next = %p\n", current_token->value,
			print_token_type(current_token->type),
			current_token->next);
		current_token = current_token->next;
	}
}
