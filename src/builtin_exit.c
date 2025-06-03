/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:06:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/21 21:19:18 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_numeric(char *value)
{
	int	i;

	i = -1;
	while (value[++i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
	}
	return (1);
}

void	clean_content(t_token **token_lst, t_env **env_lst)
{
	if (*token_lst)
		token_lst_clear(token_lst);
	if (*env_lst)
		env_lst_clear(env_lst);

}

/* TODO We need to set $? to make exit work properly */
int	builtin_exit(t_token **token_lst, t_env **env_lst)
{
	int	exit_value;	

	if ((*token_lst)->next)
	{
		if (!is_numeric((*token_lst)->next->value))
		{
			ft_printf("exit: %s: numeric argument required\n", 
				(*token_lst)->next->value);
			clean_content(token_lst, env_lst);
			exit(2);
		}
		exit_value = ft_atoi((*token_lst)->next->value);
		clean_content(token_lst, env_lst);
		exit(exit_value);
	}
	return (0);
}
