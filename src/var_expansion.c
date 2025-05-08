/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:58 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/07 14:58:59 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_dolar_pos(t_token *token_lst)
{
	int	dolar_pos;

	dolar_pos = -1;
	while (token_lst->value[++dolar_pos])
	{
		if (token_lst->value[dolar_pos] == '$')
		{
			if (ft_isalnum(token_lst->value[dolar_pos + 1]))
				return (dolar_pos);
		}
	}
	return (-1);
}

/* TODO search in internal environment variables here
* when they're ready */
void	expand_var(t_token *token)
{
	size_t	var_val_len;
	char	*new_str;
	int		dolar_pos;

	dolar_pos = -1;
	if (token->type == VAR)
	{
		if (ft_strncmp(&token->value[1], "USER", ft_strlen("USER")) == 0)
		{
			free(token->value);
			token->value = ft_strdup(USER);
		}
	}
	else if (find_dolar_pos(token) >= 1 && token->type == WORD)
	{
		dolar_pos = find_dolar_pos(token);
		var_val_len = ft_strlen(USER);
		new_str = (char *)malloc(sizeof(char) * (dolar_pos + var_val_len + 1));
		ft_memcpy(new_str, token->value, dolar_pos);
		ft_memcpy(&new_str[dolar_pos], USER, var_val_len);
		free(token->value);
		token->value = new_str;
	}
}

void	var_expansion(t_token **token_lst)
{
	token_lst_iterate(*token_lst, expand_var);
}
