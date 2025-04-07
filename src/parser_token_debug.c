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

char	*get_token_type(t_token_type type)
{
	if (type == FLAG)
		return "FLAG";
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
	return ("");
}

void	print_tokens(t_token *tokens_head)
{
	t_token	*current_token;

	current_token = tokens_head;
	printf("size -> %lu\n", token_lst_size(tokens_head));
	while (current_token)
	{
		printf("value = %s, type = %s, next = %p\n", current_token->value,
			get_token_type(current_token->type),
			current_token->next);
		current_token = current_token->next;
	}
}
