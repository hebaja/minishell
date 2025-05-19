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

int	check_integrity(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->value == NULL)
			return (0);
		token_lst = token_lst->next;
	}
	return (1);
}

void	recheck(t_token *token)
{
	define_type_builtin(token->value, &token->type);
}

void	builtin_recheck(t_token *token_lst)
{
	token_lst_iterate(token_lst, recheck);
}

/* TODO think about proper error msg when token integrity fails */
int	analyse_token_lst(t_token **token_lst)
{
	var_expansion(token_lst);
	quotes_var_expansion(token_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	builtin_recheck(*token_lst);
	if (!check_integrity(*token_lst))
		ft_putstr_fd("Token integrity fail\n", 2);
	print_tokens(*token_lst);
	return (1);
}
