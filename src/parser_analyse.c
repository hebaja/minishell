/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/23 18:55:13 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_exit_status(int status, t_token *token)
{
	char	*value;

	if (ft_strlen(token->value) == 2 && token->type == VAR
		&& token->value[1] == '?')
	{
		value = ft_itoa(status);
		free(token->value);
		token->value = value;
	}
}

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
	//create_redirect(&ms->token_lst);
	quote_removal(ms->token_lst);
	token_joining(&ms->token_lst);
	ms_token_lst_iterate(ms, expand_exit_status);
	if (!conclude_parser(ms))
		return (0);
	return (1);
}
