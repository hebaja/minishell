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

size_t	exit_status_expand_size(char *value)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (value[i])
	{
		if (value[i] && (value[i] == '$' && value[i + 1] == '?'))
			size--;
		i++;
		size++;
	}
	return (size);
}

char	*value_exit_status_build(char *value, size_t size, size_t new_size,
		char *expand_status)
{
	char		*new_value;
	size_t		ni;
	size_t		oi;

	ni = 0;
	oi = 0;
	new_value = (char *)malloc(sizeof(char) * (new_size + 1));
	if (!new_value)
		return (NULL);
	while (ni <= size)
	{
		if (value[ni] == '$' && (value[ni + 1] && value[ni + 1] == '?'))
		{
			ft_memmove(&new_value[oi], expand_status, 1);
			oi++;
			ni += 2;
		}
		else
		{
			ft_memmove(&new_value[oi], &value[ni], 1);
			oi++;
			ni++;
		}
	}
	return (new_value);
}

void	expand_exit_status(int status, t_token *token)
{
	size_t	size;
	size_t	new_size;
	char	*expand_status;
	char	*new_value;

	size = ft_strlen(token->value);
	expand_status = ft_itoa(status);
	new_size = exit_status_expand_size(token->value);
	if (new_size > 0)
	{
		new_value = value_exit_status_build(token->value, size,
				new_size, expand_status);
		if (new_value)
		{
			free(token->value);
			token->value = new_value;
		}
	}
	free(expand_status);
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
	quote_removal(ms->token_lst);
	token_joining(&ms->token_lst);
	ms_token_lst_iterate(ms, expand_exit_status);
	if (!conclude_parser(ms))
		return (0);
	return (1);
}
