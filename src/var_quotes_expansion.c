/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_quotes_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:28:19 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/09 02:28:22 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_in_quote(t_token *token_lst, t_env *env_lst, int dolar_pos)
{
	char	*key;

	key = extract_var_key(token_lst, dolar_pos);
	join_value(key, token_lst, env_lst, dolar_pos);
	return (1);
}

void	check_double_quoted(t_token *token_lst, t_env *env_lst)
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
				expand_in_quote(token_lst, env_lst, dolar_pos);
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

void	quotes_var_expansion(t_token **token_lst, t_env *env_lst)
{
	token_lst_env_iterate(*token_lst, env_lst, check_double_quoted);
}
