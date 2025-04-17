/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_build.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:26 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/06 14:29:31 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_build(char **o_value, char *value_start, size_t size)
{
	t_token	*token;
	char	*value;

	token = (t_token *)malloc(sizeof(t_token));
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (*value_start == '\'' || *value_start == '\"')
		value_start++;
	ft_strlcpy(value, value_start, size + 1);
	if (!token || !value)
		return (NULL);
	token->type = define_type(value);
	token->value = value;
	token->next = NULL;
	*o_value = (*o_value) + size;
	return (token);
}

int	append_token(t_token **tokens_head, char **value,
	char *value_start, size_t size)
{
	t_token		*token;

	if (*value_start)
	{
		if (tokens_head == NULL || *tokens_head == NULL)
		{
			token = token_build(value, value_start, size);
			if (!token)
				return (0);
			*tokens_head = token;
		}
		else
		{
			token = token_build(value, value_start, size);
			if (!token)
			{
				token_lst_clear(tokens_head);
				return (0);
			}
			token_lst_add_back(tokens_head, token);
		}
	}
	return (1);
}

int	build_token_metacharacter(t_token **tokens_head, char **value)
{
	int		size;
	char	*value_start;

	if (*value)
	{
		size = is_meta_token(*value);
		value_start = *value;
		if (!append_token(tokens_head, value, value_start, size))
			return (0);
		*value = *value + size;
	}
	return (1);
}

int	default_build(t_token **tokens_head,
	char **value, char *value_start, int i)
{
	while ((*value)[i] && !ft_isspace((*value)[i])
		&& !is_metacharacter((*value)[i]))
		i++;
	if (*value_start == '\'')
	{
		if (!quote_mode(tokens_head, value, value_start, '\''))
			return (0);
	}
	else if (*value_start == '\"')
	{
		if (!quote_mode(tokens_head, value, value_start, '\"'))
			return (0);
	}
	else if (!append_token(tokens_head, value, value_start, i))
		return (0);
	return (1);
}

int	token_lst_build(t_token **tokens_head, char *value)
{
	size_t		i;
	char		*value_start;

	i = 0;
	value_start = value;
	while (value[i])
	{
		if (value[i] && is_metacharacter(value[i]))
		{
			while (is_metacharacter(value[i]))
				i++;
			if (!append_token(tokens_head, &value, value_start, i))
				return (0);
		}
		else
		{
			if (!default_build(tokens_head, &value, value_start, i))
				return (0);
		}
		while (value && ft_isspace(*value))
			value++;
		value_start = value;
		i = 0;
	}
	return (1);
}
