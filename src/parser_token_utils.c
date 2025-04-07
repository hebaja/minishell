/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:44 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/06 14:29:48 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_lst_last(t_token *token_lst)
{
	t_token	*current_token;

	current_token = token_lst;
	while (current_token)
	{
		if (current_token->next == NULL)
			break ;
		current_token = current_token->next;
	}
	return (current_token);
}

void	token_lst_add_back(t_token **token_lst_head, t_token *token)
{
	if (*token_lst_head == NULL)
		*token_lst_head = token;
	else
		token_lst_last(*token_lst_head)->next = token;
}

void	token_clear(t_token *token)
{
	if (!token)
		return ;
	token->next = NULL;
	free(token->value);
	free(token);
	token = NULL;
}

void	token_lst_clear(t_token **token_lst_head)
{
	t_token	*token;
	t_token	*token_tmp;

	token = *token_lst_head;
	if (token)
	{
		token_tmp = token;
		token = token->next;
		token_clear(token_tmp);
	}
	*token_lst_head = NULL;
}
