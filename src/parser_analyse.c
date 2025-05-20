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


/* TODO think about proper error msg when token integrity fails */
int	analyse_token_lst(t_token **token_lst)
{
	var_expansion(token_lst);
	quotes_var_expansion(token_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	conclude_parser(*token_lst);
	print_tokens(*token_lst);
	return (1);
}
