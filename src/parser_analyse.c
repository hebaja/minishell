/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/07 14:58:44 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* TODO still to implement:
 * - quotes removal
 * - joining tokens  
 * - checking lst integrity
*/

/*
void	check_token_join(t_token *token)
{
	char	*new_str;
	t_token	*n_token;

	if (!token)
		return ;
	n_token = token->next;
	if (n_token && (n_token->type == WORD_JOIN || n_token->type == VAR_JOIN))
	{
		new_str = ft_strjoin(token->value, n_token->value);
		free(token->value);
		
		token->next = n_token->next;
		token_clear(n_token);
		n_token = NULL;
		
		token->value = new_str;
	}
}
*/

int	cmp(t_token_type a, t_token_type b)
{
	if (a == b)
		return (1);
	return (0);
}

void	token_joining(t_token **token_lst)
{
	// t_token	*fixed;
	t_token	*current;
	t_token	*n_token;
	char	*new_str;

	current = *token_lst;
	if (!current)
		return ;
	if (current && current->next && (current->next->type == WORD_JOIN || current->next->type == VAR_JOIN))
	{
		// fixed = current;
		n_token = current->next;
		// var_expansion(&n_token);
		// quotes_var_expansion(&n_token);
		// quote_removal(n_token);
		while (n_token && (n_token->type == WORD_JOIN || n_token->type == VAR_JOIN))
		{
			new_str = ft_strjoin(current->value, n_token->value);
			free(current->value);
			current->value = new_str;
			n_token = n_token->next;
		}
		token_joining(&n_token);
	}
	else
	{
		token_joining(&current->next);
	}
	
	// token_lst_iterate(*token_lst, check_token_join);
	token_lst_remove_if(token_lst, WORD_JOIN, cmp);
	token_lst_remove_if(token_lst, VAR_JOIN, cmp);
}

int	analyse_token_lst(t_token **token_lst)
{
	var_expansion(token_lst);
	quotes_var_expansion(token_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	print_tokens(*token_lst);
	return (1);
}
