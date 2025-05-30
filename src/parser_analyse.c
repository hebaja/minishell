/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/29 20:59:48 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	iscommandtoken(t_token *token_head, t_env **env)
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
	t_token *tmp;

	tmp = *token_lst;
	quotes_var_expansion(token_lst);
	create_redicter(token_lst);
	token_lst = &tmp;
	ft_printf("%d\n", (*token_lst)->fd);
	quote_removal(*token_lst);
	token_joining(token_lst);
	conclude_parser(*token_lst);
	iscommandtoken(*token_lst, &environment_variables);
	execute(*token_lst);
	print_tokens(*token_lst);
	return (1);
}
