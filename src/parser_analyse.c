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

void	builtin_echo(t_token *token_lst)
{
	if (token_lst->next && ft_strcmp(token_lst->next->value,"-n") == 0)
		ft_printf("%s", token_lst->next->next->value);
	else if (token_lst->next)
		ft_printf("%s\n", token_lst->next->value);
	else
		ft_printf("\n");
}

/* TODO think about proper error msg when token integrity fails */
int	analyse_token_lst(t_token **token_lst)
{
	int	res;

	var_expansion(token_lst);
	quotes_var_expansion(token_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	conclude_parser(*token_lst);
	res = check_redirect(*token_lst);
	if (res == -1)
		ft_putstr_fd("Syntax error\n", 2);
	else
	{
		print_tokens(*token_lst);
		if ((*token_lst)->type == BUILTIN_ECHO)
			builtin_echo(*token_lst);
	}
	return (1);
}
