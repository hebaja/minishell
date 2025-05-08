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

int	comp(t_token_type type_a, t_token_type type_b)
{
	if (type_a == type_b)
		return (1);
	return (0);
}

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

void	token_lst_add_back(t_token **token_lst, t_token *token)
{
	if (*token_lst == NULL)
		*token_lst = token;
	else
		token_lst_last(*token_lst)->next = token;
}

size_t	token_lst_size(t_token *token_lst)
{
	size_t	size;

	if (!token_lst)
		return (0);
	size = 0;
	while (token_lst)
	{
		size++;
		token_lst = token_lst->next;
	}
	return (size);
}

void	token_lst_iterate(t_token *token_lst, void(func)(t_token *))
{
	t_token	*next_token;

	if (token_lst == NULL)
		return ;
	while (token_lst)
	{
		next_token = token_lst->next;
		func(token_lst);
		token_lst = next_token;
	}
}

void token_lst_remove_if(t_token **token_lst, t_token_type type, int (*cmp)())
{
	t_token	*token;

	if (token_lst == NULL || *token_lst == NULL)
		return ;
	token = *token_lst;
	if (cmp(token->type, type))
	{
		*token_lst = token->next;
		token_clear(token);
		token_lst_remove_if(token_lst, type, cmp);
	}
	else
	{
		token = *token_lst;
		token_lst_remove_if(&token->next, type, cmp);
	}
}
