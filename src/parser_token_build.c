/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_build.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:26 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/20 11:22:48 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_build(char **abs_value, char *value_start, size_t size)
{
	t_token	*token;
	char	*value;
	char	quote;

	quote = 0;
	token = (t_token *)malloc(sizeof(t_token));
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (!token || !value)
		return (NULL);
	if (*value_start == '\'' || *value_start == '\"')
	{
		quote = *value_start;
		value_start++;
	}
	ft_strlcpy(value, value_start, size + 1);
	token->type = define_type(value, quote);
	set_extra_meta_chars(token, value_start, quote);
	token->value = value;
	token->next = NULL;
	*abs_value = (*abs_value) + size;
	return (token);
}

int	append_token(t_token **token_lst, char **value,
	char *value_start, size_t size)
{
	t_token		*token;

	if (*value_start)
	{
		if (token_lst == NULL || *token_lst == NULL)
		{
			token = token_build(value, value_start, size);
			if (!token)
				return (0);
			*token_lst = token;
		}
		else
		{
			token = token_build(value, value_start, size);
			if (!token)
			{
				token_lst_clear(token_lst);
				return (0);
			}
			token_lst_add_back(token_lst, token);
		}
	}
	return (1);
}

// int	build_token_metacharacter(t_token **token_lst, char **value)
// {
// 	int		size;
// 	char	*value_start;

// 	if (*value)
// 	{
// 		size = is_meta_token(*value);
// 		value_start = *value;
// 		if (!append_token(token_lst, value, value_start, size))
// 			return (0);
// 		*value = *value + size;
// 	}
// 	return (1);
// }
int	regular_mode(t_token **token_lst, char **value, char *value_start, int i)
{
	char	quote;

	quote = 0;
	while ((*value)[i] && !is_metacharacter((*value)[i]) && !is_dolar(*value))
	{
		if (!quote && ft_isspace((*value)[i]))
			break ;
		else if (quote && (*value)[i] == quote)
		{
			i++;
			break ;
		}
		else if ((*value)[i] == '\'' || (*value)[i] == '\"')
			quote = (*value)[i];
		i++;
		if (quote && !(*value)[i])
			return (0);
	}
	if (!append_token(token_lst, value, value_start, i))
		return (0);
	return (1);
}

int	default_build(t_token **token_lst,
	char **value, char *value_start, int i)
{
	if (*value_start == '\'')
	{
		if (!quote_mode(token_lst, value, value_start, '\''))
			return (0);
	}
	else if (*value_start == '\"')
	{
		if (!quote_mode(token_lst, value, value_start, '\"'))
			return (0);
	}
	else if (is_dolar(*value))
	{
		if (!var_mode(token_lst, value, value_start))
			return (0);
	}
	else
		if (!regular_mode(token_lst, value, value_start, i))
			return (0);
	return (1);
}

int	token_lst_build(t_token **token_lst, char *value)
{
	size_t		i;
	char		*value_start;

	i = 0;
	value_start = value;
	while (value[i])
	{
		if (value[i] && (is_metacharacter(value[i])))
		{
			while (i < 2 && (is_metacharacter(value[i])))
				i++;
			if (!append_token(token_lst, &value, value_start, i))
				return (0);
		}
		else
		{
			if (!default_build(token_lst, &value, value_start, i))
				return (0);
		}
		while (value && ft_isspace(*value))
			value++;
		value_start = value;
		i = 0;
	}
	return (1);
}
