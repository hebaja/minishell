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

int	quote_mode(t_token **tokens_head, char **value, char quote)
{
	size_t	size;
	char	*value_start;
	int		flag_close;

	size = 0;
	value_start = *value;
	(*value)++;
	flag_close = 0;
	while (**value && **value != quote)
	{
		size++;
		(*value)++;
	}
	if (**value != quote)
	{
		ft_putstr_fd("Unclosed quotes\n", 2);
		return (0);
	}
	append_token(tokens_head, value_start, size);
	(*value)++;
	return (1);
}

int	is_metacharacter(char *value)
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
