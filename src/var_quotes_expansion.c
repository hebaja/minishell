/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_quotes_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:28:19 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/02 19:21:46 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	define_new_value(t_token *token_lst, int dolar_pos)
{
	char	*new_str;
	int		var_value_len;
	int		var_key_len;
	int		old_value_len;
	int		new_value_len;

	var_value_len = ft_strlen(USER);
	var_key_len = ft_strlen("USER");
	old_value_len = ft_strlen(token_lst->value);
	new_value_len = (old_value_len - var_key_len) + var_value_len;
	new_str = (char *)malloc(sizeof(char) * (new_value_len + 1));
	if (new_str == NULL)
		return (0);
	ft_memcpy(new_str, token_lst->value, dolar_pos);
	ft_memcpy(&new_str[dolar_pos], USER, var_value_len);
	ft_memcpy(&new_str[dolar_pos + var_value_len],
		&token_lst->value[dolar_pos + var_key_len + 1],
		old_value_len - var_key_len - dolar_pos);
	free(token_lst->value);
	token_lst->value = new_str;
	return (1);
}

/* TODO search in internal environment variables here
* when they're ready */
int	expand_in_quote(t_token *token_lst, int dolar_pos)
{
	int		env_name_len;
	char	*env_name;
	int		i;

	i = 0;
	env_name_len = 0;
	while (token_lst->value[i] != '$')
		i++;
	while (ft_isalnum(token_lst->value[++i]))
		env_name_len++;
	env_name = ft_substr(token_lst->value, dolar_pos + 1, env_name_len);
	if (ft_strncmp(env_name, "USER", ft_strlen(env_name)) == 0)
		define_new_value(token_lst, dolar_pos);
	free(env_name);
	return (1);
}

void	check_double_quoted(t_token *token_lst)
{
	int	dolar_pos;
	int	i;

	i = 0;
	if (token_lst->type == DOUBLE_QUOTED)
	{
		dolar_pos = find_dolar_pos(token_lst);
		if (dolar_pos >= 0)
		{
			i = dolar_pos;
			while (token_lst->value[i])
			{
				expand_in_quote(token_lst, dolar_pos);
				i++;
				while (token_lst->value[i] && token_lst->value[i] != '$')
					i++;
				dolar_pos = find_dolar_pos(token_lst);
				if (dolar_pos >= 0)
					i = dolar_pos;
			}
		}
	}
}

int		quotes_var_expansion(t_token **token_lst)
{
	int	value;

	value = token_lst_iterate(*token_lst, check_double_quoted);
	return (value);
}
