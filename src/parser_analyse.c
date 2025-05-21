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

void	iscommandToken(t_token *token_head, t_env **env)
{
	if (token_head->type == BUILTIN_CD)
		builtin_cd(token_head);
	else if (token_head->type == BUILTIN_PWD)
		builtin_pwd();
	else if (token_head->type == BUILTIN_ECHO)
		builtin_echo(token_head);
	else if (token_head->type == BUILTIN_ENV)
		builtin_env(*env);
	else if (token_head->type == BUILTIN_EXPORT)
		builtin_export(token_head, *env);
	else if (token_head->type == BUILTIN_UNSET)
		builtin_unset(env, token_head);
	else if (token_head->type == BUILTIN_EXIT)
		builtin_exit(token_head);
}

/* TODO think about proper error msg when token integrity fails */
int	analyse_token_lst(t_token **token_lst, t_env *environment_variables)
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
