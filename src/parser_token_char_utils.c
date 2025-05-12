/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_char_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:35:48 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/14 01:35:50 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_metacharacter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '*')
		return (1);
	return (0);
}

int	is_dolar(char *value)
{
	if (value == NULL || *value == '\0' || *value != '$')
		return (0);
	else if (*value == '$')
		value++;
	if (*value && ft_isalnum(*value))
		return (1);
	return (0);
}

int	var_mode(t_token **token_lst, char **value, char *value_start)
{
	int	size;

	size = 1;
	while (ft_isalnum((*value)[size]))
		size++;
	append_token(token_lst, value, value_start, size);
	return (1);
}

int	quote_mode(t_token **token_lst, char **value,
	char *quoted_value, char quote)
{
	size_t	size;
	char	*value_start;

	size = 0;
	value_start = quoted_value;
	quoted_value++;
	if (*quoted_value)
	{
		while (*quoted_value && *quoted_value != quote)
		{
			size++;
			quoted_value++;
		}
		if (*quoted_value != quote)
		{
			ft_putstr_fd("Unclosed quotes\n", 2);
			return (0);
		}
		append_token(token_lst, value, value_start, size);
		quoted_value++;
		*value = quoted_value;
	}
	return (1);
}

int	is_meta_token(char *value)
{
	if (ft_strncmp(value, "\'", 1) == 0)
		return (4);
	if (ft_strncmp(value, "\"", 1) == 0)
		return (3);
	if ((ft_strncmp(value, ">>", 2) == 0) || (ft_strncmp(value, "<<", 2) == 0)
		|| (ft_strncmp(value, "&&", 2) == 0)
		|| (ft_strncmp(value, "||", 2) == 0))
		return (2);
	if ((ft_strncmp(value, "|", 1) == 0) || (ft_strncmp(value, ">", 1) == 0)
		|| (ft_strncmp(value, "<", 1) == 0)
		|| (ft_strncmp(value, "&", 1) == 0))
		return (1);
	return (0);
}
