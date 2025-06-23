/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:34:05 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/23 19:26:00 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_dolar_pos(t_token *token_lst)
{
	int	dolar_pos;

	if (!token_lst->value)
		return (-1);
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

void	join_value(char *key, t_token *token, t_env *env_lst, int dolar_pos)
{
	char	*val;
	char	*new_str;
	size_t	val_len;
	size_t	key_len;
	size_t	end_val_offset;

	end_val_offset = 0;
	val = get_var_value(env_lst, key);
	if (!val)
		return ;
	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	if (ft_strlen(token->value) > (dolar_pos + key_len + 1))
		end_val_offset = ft_strlen(token->value) - (key_len + 1);
	new_str = ft_calloc(dolar_pos + val_len
			+ end_val_offset + 1, sizeof(char));
	ft_memcpy(new_str, token->value, dolar_pos);
	ft_memcpy(&new_str[dolar_pos], val, val_len);
	ft_memcpy(&new_str[dolar_pos + val_len],
		&token->value[dolar_pos + key_len + 1], end_val_offset);
	free(token->value);
	token->value = new_str;
}

char	*extract_var_key(t_token *token, int dolar_pos)
{
	int		i;
	int		key_len;
	char	*key;

	i = 0;
	key_len = 0;
	while (token->value[i] != '$')
		i++;
	while (ft_isalnum(token->value[++i]))
		key_len++;
	key = ft_substr(token->value, dolar_pos + 1, key_len);
	return (key);
}
