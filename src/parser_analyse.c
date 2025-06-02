/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/26 19:19:08 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	analyse_token_lst(t_token **token_lst, t_env *env_lst)
{
	var_expansion(token_lst, env_lst);
	quotes_var_expansion(token_lst, env_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	if (!conclude_parser(*token_lst))
		return (0);
	// print_tokens(*token_lst);
	return (1);
}
