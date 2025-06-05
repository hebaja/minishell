/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:44 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/06 14:29:48 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* TODO Not sure if this is necessary
char	*set_arg(t_token *token_lst)
{
	char	*arg;

	if (token_lst->type != SINGLE_QUOTED && token_lst->type != DOUBLE_QUOTED)
		arg = ft_strtrim(token_lst->value, " \t");
	else
		arg = ft_strdup(token_lst->value);
	return (arg);
}
*/

char	**split_token_value(t_token *token_lst, size_t cmd_size)
{
	int		i;
	char	**args;

	i = 0;
	args = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	while (cmd_size)
	{
		args[i] = ft_strdup(token_lst->value);
		token_lst = token_lst->next;
		cmd_size--;
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_token	*token_lst_last(t_token *token_lst)
{
	t_token	*current_token;

	current_token = token_lst;
	while (current_token)
	{
		if (current_token->next == NULL)
			break ;
		current_token = current_token->next;
	}
	return (current_token);
}

void	token_lst_add_back(t_token **token_lst, t_token *token)
{
	if (*token_lst == NULL)
		*token_lst = token;
	else
		token_lst_last(*token_lst)->next = token;
}

size_t	token_lst_size(t_token *token_lst)
{
	size_t	size;

	if (!token_lst)
		return (0);
	size = 0;
	while (token_lst)
	{
		size++;
		token_lst = token_lst->next;
	}
	return (size);
}

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

void	token_lst_env_iterate(t_token *token_lst, t_env *env_lst, void (*func)(t_token *, t_env *))
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
