/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:08:20 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/09 01:08:22 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_clear(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
	token = NULL;
}

void	token_lst_clear(t_token **token_lst)
{
	if (token_lst != NULL)
		token_lst_iterate(*token_lst, token_clear);
	*token_lst = NULL;
}

void	token_lst_join_remove(t_token **token_lst)
{
	t_token	*current;

	if (token_lst == NULL || *token_lst == NULL)
		return ;
	current = *token_lst;
	if (current->join)
	{
		*token_lst = current->next;
		token_clear(current);
		token_lst_join_remove(token_lst);
	}
	else
	{
		current = *token_lst;
		token_lst_join_remove(&current->next);
	}
}
