/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_build.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:26 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/08 21:43:32 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	append_token(t_token **tokens_head, char *value_start, size_t size)
{
	t_token		*token;

	if (tokens_head == NULL || *tokens_head == NULL)
	{
		token = token_build(value_start, size);
		if (!token)
			return (0);
		*tokens_head = token;
	}
	else
	{
		token = token_build(value_start, size);
		if (!token)
		{
			token_lst_clear(tokens_head);
			return (0);
		}
		token_lst_add_back(tokens_head, token);
	}
	return (1);
}

int	build_token_metacharacter(t_token **tokens_head, char **value)
{
	int		size;
	char	*value_start;

	size = is_metacharacter(*value);
	value_start = *value;
	if (!append_token(tokens_head, value_start, size))
		return (0);
	*value = *value + size;
	return (1);
}

int	determine_token_type(t_token **tokens_head, char **value,
	char *value_start, size_t size)
{
	if (size)
		if (!append_token(tokens_head, value_start, size))
			return (0);
	if (*value && is_metacharacter(*value))
		if (!build_token_metacharacter(tokens_head, value))
			return (0);
	if (ft_isspace(**value))
		while (*value && ft_isspace(**value))
			(*value)++;
	return (1);
}

int	token_lst_build(t_token **tokens_head, char *value)
{
	char		*value_start;
	size_t		size;

	size = 0;
	value_start = value;
	while (*value)
	{
		while (*value && (!ft_isspace(*value) && !is_metacharacter(value)))
		{
			value++;
			size++;
		}
		if (!determine_token_type(tokens_head, &value, value_start, size))
			return (0);
		if (*value)
			value_start = value;
		size = 0;
	}
	return (1);
}
