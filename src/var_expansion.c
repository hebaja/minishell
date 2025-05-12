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

int	single_quote_precedes(char *value, int i)
{
	while (i >= 0)
	{
		if (value[i] == '\'')
			return (1);
		i--;
	}
	return (0);
}

int	deal_mixed_value(t_token *token, int dolar_pos)
{
	size_t	var_val_len;
	size_t	var_key_len;
	char	*new_str;
	int		cut_size;
	int		new_size;

	var_val_len = ft_strlen(USER);
	var_key_len = ft_strlen("USER");

	cut_size = dolar_pos + var_key_len + 1;
	new_size = ft_strlen(token->value) - cut_size;

	// new_str = (char *)malloc(sizeof(char) * (dolar_pos + var_val_len + new_size + 1));
	new_str = ft_calloc(dolar_pos + var_val_len + new_size + 1, sizeof(char));
	if (!new_str)
		return (0);
	ft_memcpy(new_str, token->value, dolar_pos);
	ft_memcpy(&new_str[dolar_pos], USER, var_val_len);
	ft_memcpy(&new_str[dolar_pos + var_val_len],
		&token->value[dolar_pos + var_key_len + 1],
		new_size);
	free(token->value);
	token->value = new_str;
	return (1);
}

/* TODO search in internal environment variables here
* when they're ready 
* */
void	expand_var(t_token *token)
{
	int		dolar_pos;

	dolar_pos = find_dolar_pos(token);
	if (token->type == VAR)
	{
		if (ft_strncmp(&token->value[1], "USER", ft_strlen("USER") + 1) == 0)
		{
			free(token->value);
			token->value = ft_strdup(USER);
		}
	}
	else if (token->type == WORD && dolar_pos >= 1
		&& !single_quote_precedes(token->value, dolar_pos))
	deal_mixed_value(token, dolar_pos);
}

void	var_expansion(t_token **token_lst)
{
	token_lst_iterate(*token_lst, expand_var);
}
