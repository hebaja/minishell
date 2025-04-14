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

t_token	*token_build(char *value_start, size_t size)
{
	t_token	*token;
	char	*value;

	token = (t_token *)malloc(sizeof(t_token));
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (!token || !value)
		return (NULL);
	ft_strlcpy(value, value_start, size + 1);
	token->value = value;
	token->type = define_type(value);
	token->next = NULL;
	return (token);
}

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

int	is_metacharacter(char *value)
{
	if ((ft_strncmp(value, ">>", 2) == 0) || (ft_strncmp(value, "<<", 2) == 0) || (ft_strncmp(value, "&&", 2) == 0) || (ft_strncmp(value, "||", 2) == 0))
 		return (2);
	if ((ft_strncmp(value, "|", 1) == 0) || (ft_strncmp(value, ">", 1) == 0) || (ft_strncmp(value, "<", 1) == 0) || (ft_strncmp(value, "&", 1) == 0))
		return (1);
	return (0);
}

int	token_lst_build(t_token **tokens_head, char *value)
{
	size_t		size;
	char		*value_start;

	value_start = value;
	size = 0;
	while (*value)
	{
		while (*value && (!ft_isspace(*value) && !is_metacharacter(value)))
		{
			value++;
			size++;
		}
		if (size)
			if (!append_token(tokens_head, value_start, size))
				return (0);
		if (*value && is_metacharacter(value))
		{
			size = is_metacharacter(value);
			value_start = value;
			if (!append_token(tokens_head, value_start, size))
				return (0);
			value = value + size;
		}
		if (ft_isspace(*value))
			while (*value && ft_isspace(*value))
				value++;
		if (*value)
			value_start = value;
		size = 0;
	}
	return (1);
}
