/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:56:34 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/14 14:56:37 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	there_is_quote(char *value)
{
	if (value && (ft_strchr(value, '\'') || ft_strchr(value, '\"')))
		return (1);
	return (0);
}

void	remove_quotes(t_token *token)
{
	int		i;
	int		offset;
	char	*new_value;
	size_t	value_len;

	if ((token->type == WORD) 
		&& there_is_quote(token->value))
	{
		i = -1;
		offset = 0;
		value_len = ft_strlen(token->value);
		new_value = ft_calloc(value_len - 1, sizeof(char));
		while (token->value[++i])
		{
			if (token->value[i] != '\'' && token->value[i] != '\"')
				ft_memcpy(&new_value[i - offset], &token->value[i], 1);
			else
				offset++;
		}
		new_value[i - offset] = '\0';
		free(token->value);
		token->value = new_value;
	}
}

void	quote_removal(t_token *token_lst)
{
	token_lst_iterate(token_lst, remove_quotes);
}
