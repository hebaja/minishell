/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/02 19:47:43 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	iscommandtoken(t_token *token_head, t_env **env)
{
	int	value;

	value = 0;
	if (token_head->type == BUILTIN_CD)
		value = builtin_cd(token_head);
	else if (token_head->type == BUILTIN_PWD)
		value = builtin_pwd();
	else if (token_head->type == BUILTIN_ECHO)
		value = builtin_echo(token_head);
	else if (token_head->type == BUILTIN_ENV)
		value = builtin_env(*env);
	else if (token_head->type == BUILTIN_EXPORT)
		value = builtin_export(token_head, *env);
	else if (token_head->type == BUILTIN_UNSET)
		value = builtin_unset(env, token_head);
	else if (token_head->type == BUILTIN_EXIT)
		builtin_exit(token_head);
	return (value);
}

/* TODO think about proper error msg when token integrity fails */
int	analyse_token_lst(t_token **token_lst, t_env *environment_variables)
{
	t_token *tmp;
	int	value;

	tmp = *token_lst;
	quotes_var_expansion(token_lst);
	create_redicter(token_lst);
	token_lst = &tmp;
	quote_removal(*token_lst);
	token_joining(token_lst);
	conclude_parser(*token_lst);
	value = iscommandtoken(*token_lst, &environment_variables);
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("%d\n", value);
	ft_printf("\n");
	//execute(*token_lst);
	print_tokens(*token_lst);
	return (1);
}
