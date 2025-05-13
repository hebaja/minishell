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

/* We'll have to handle possible calloc error here
 */
void	deal_mixed_value(t_token *token, int dolar_pos)
{
	size_t	var_val_len;
	size_t	var_key_len;
	size_t	end_val_offset;
	char	*new_str;

	var_val_len = ft_strlen(USER);
	var_key_len = ft_strlen("USER");
	end_val_offset = ft_strlen(token->value) - (dolar_pos + var_key_len + 1);
	new_str = ft_calloc(dolar_pos + var_val_len
		+ end_val_offset + 1, sizeof(char));
	ft_memcpy(new_str, token->value, dolar_pos);
	ft_memcpy(&new_str[dolar_pos], USER, var_val_len);
	ft_memcpy(&new_str[dolar_pos + var_val_len],
		&token->value[dolar_pos + var_key_len + 1], end_val_offset);
	free(token->value);
	token->value = new_str;
}

/* TODO search in internal environment variables here
* when they're ready 
* */
void	expand_var(t_token *token)
{
	int		dolar_pos;

	dolar_pos = find_dolar_pos(token);
	if (token->type == VAR || token->type == VAR_JOIN)
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
