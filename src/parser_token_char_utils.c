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
	if (*value && (ft_isalnum(*value) || *value == '?'))
		return (1);
	return (0);
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
