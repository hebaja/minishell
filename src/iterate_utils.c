/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:46:58 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/04 23:47:00 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_lst_iterate(t_token *token_lst, void (*func)(t_token *))
{
	t_token	*next_token;

	if (token_lst == NULL)
		return ;
	while (token_lst)
	{
		next_token = token_lst->next;
		func(token_lst);
		token_lst = next_token;
	}
}

void	token_lst_env_iterate(t_token *token_lst, t_env *env_lst,
	void (*func)(t_token *, t_env *))
{
	t_token	*next_token;

	if (token_lst == NULL)
		return ;
	while (token_lst)
	{
		next_token = token_lst->next;
		func(token_lst, env_lst);
		token_lst = next_token;
	}
}

int	token_lst_iterate_check(t_token *token_lst, int (*func)(t_token *))
{
	t_token	*next_token;
	int		res;
	int		tmp;

	res = 0;
	tmp = 0;
	if (token_lst == NULL)
		return (-1);
	while (token_lst)
	{
		next_token = token_lst->next;
		tmp = func(token_lst);
		if (tmp == -1)
			return (-1);
		res += tmp;
		token_lst = next_token;
	}
	return (res);
}

void	cmd_lst_iterate(t_cmd *cmd_lst,	void (*func)(t_cmd *))
{
	t_cmd	*next_cmd;

	if (cmd_lst == NULL)
		return ;
	while (cmd_lst)
	{
		next_cmd = cmd_lst->next;
		func(cmd_lst);
		cmd_lst = next_cmd;
	}
}

void	env_lst_iterate(t_env *env_lst, void (*func)(t_env *env_lst))
{
	t_env	*next_env;

	if (!env_lst)
		return ;
	while (env_lst)
	{
		next_env = env_lst->next;
		func(env_lst);
		env_lst = next_env;
	}
}
