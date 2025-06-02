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

void	expand_var(t_token *token, t_env *env_lst)
{
	int		dolar_pos;
	char	*value;
	char	*key;

	if (!token->value)
		return ;
	dolar_pos = find_dolar_pos(token);
	if (token->type == VAR)
	{
		value = get_var_value(env_lst, &token->value[1]);
		if (value != NULL)
		{
			free(token->value);
			token->value = ft_strdup(value);
		}
	}
	else if ((token->type == WORD)
		&& dolar_pos >= 1 && !single_quote_precedes(token->value, dolar_pos))
	{
		key = extract_var_key(token, dolar_pos);
		join_value(key, token, env_lst, dolar_pos);
	}
}

void	var_expansion(t_token **token_lst, t_env *env_lst)
{
	token_lst_env_iterate(*token_lst, env_lst, expand_var);
}
