/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_conclusion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:49:49 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 19:49:52 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(t_token_type type)
{
	if (type == REDIRECT_OUT || type == REDIRECT_IN || type == APPEND
		|| type == HEREDOC || type == PIPE)
		return (1);
	return (0);
}

int	redirect_validate(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->type == REDIRECT_IN || token_lst->type == REDIRECT_OUT
			|| token_lst->type == PIPE)
		{
			if (!token_lst->next || ft_strlen(token_lst->value) != 1
				|| is_redirect(token_lst->next->type))
			{
				ft_putendl_fd("Syntax error", 2);
				return (0);
			}
		}
		if (token_lst->type == HEREDOC || token_lst->type == APPEND)
		{
			if (!token_lst->next || ft_strlen(token_lst->value) != 2
				|| is_redirect(token_lst->next->type))
			{
				ft_putendl_fd("Syntax error", 2);
				return (0);
			}
		}
		token_lst = token_lst->next;
	}
	return (1);
}

int	check_token_integrity(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->value == NULL)
		{
			ft_putendl_fd("Problem building tokens", 2);
			return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

void	builtin_recheck(t_token *token)
{
	if (token->value)
		define_type_builtin(token->value, &token->type);
}

int	conclude_parser(t_ms *ms)
{
	token_lst_iterate(ms->token_lst, builtin_recheck);
	if (!check_token_integrity(ms->token_lst))
		return (0);
	if (!redirect_validate(ms->token_lst))
		return (0);
	return (1);
}
