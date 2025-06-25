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

void	ms_token_lst_iterate(t_ms *ms, void (*func)(int, t_token *))
{
	t_token	*curr_token;
	t_token	*next_token;

	if (!ms || !ms->token_lst)
		return ;
	curr_token = ms->token_lst;
	while (curr_token)
	{
		next_token = curr_token->next;
		func(ms->status, curr_token);
		curr_token = next_token;
	}
}

int	analyse_token_lst(t_ms *ms)
{
	var_expansion(&ms->token_lst, ms->env_lst);
	quotes_var_expansion(&ms->token_lst, ms->env_lst);
	quote_removal(ms->token_lst);
	token_joining(&ms->token_lst);
	ms_token_lst_iterate(ms, expand_exit_status);
	if (!conclude_parser(ms))
		return (0);
	return (1);
}
