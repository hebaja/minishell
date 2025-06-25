/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_status_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:21:18 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/25 11:21:20 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	exit_status_expand_size(char *value, size_t exp_status_size)
{
	int		i;
	int		flag;
	size_t	size;

	i = 0;
	flag = 0;
	size = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			flag = 1;
			if (value[i] && exp_status_size == 1)
				size--;
			if (value[i] && exp_status_size == 2)
				size = size;
			if (value[i] && exp_status_size == 3)
				size++;
		}
		i++;
		size++;
	}
	if (!flag)
		return (0);
	return (size);
}

char	*populate_expand_exit_value(char *value, char *expand_status,
		size_t new_size, size_t exp_status_size)
{
	size_t		ni;
	size_t		oi;
	char		*new_value;

	ni = 0;
	oi = 0;
	new_value = (char *)malloc(sizeof(char) * (new_size + 1));
	if (!new_value)
		return (NULL);
	while (ni <= new_size)
	{
		if (value[oi] == '$' && (value[oi + 1] && value[oi + 1] == '?'))
		{
			ft_memmove(&new_value[ni], expand_status, exp_status_size);
			oi += 2;
			ni += exp_status_size;
		}
		else
		{
			ft_memmove(&new_value[ni], &value[oi], 1);
			ni++;
			oi++;
		}
	}
	return (new_value);
}

char	*value_exit_status_build(char *value, size_t new_size,
		char *expand_status)
{
	char		*new_value;
	size_t		exp_status_size;

	exp_status_size = ft_strlen(expand_status);
	new_value = populate_expand_exit_value(value, expand_status, new_size,
			exp_status_size);
	return (new_value);
}

void	expand_exit_status(int status, t_token *token)
{
	size_t	new_size;
	size_t	exp_status_size;
	char	*exp_status;
	char	*new_value;

	exp_status = ft_itoa(status);
	exp_status_size = ft_strlen(exp_status);
	new_size = exit_status_expand_size(token->value, exp_status_size);
	if (new_size > 0)
	{
		new_value = value_exit_status_build(token->value,
				new_size, exp_status);
		if (new_value)
		{
			free(token->value);
			token->value = new_value;
		}
	}
	free(exp_status);
}
