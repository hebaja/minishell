/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:04:41 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/14 18:04:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (1);
	}
	ft_putstr_fd("Unclosed quotes\n", 2);
	return (0);
}

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
		{
			ft_putstr_fd("Unclosed quotes\n", 2);
			return (0);
		}
	}
	if (!append_token(token_lst, value, value_start, i))
		return (0);
	return (1);
}
