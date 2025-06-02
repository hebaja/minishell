/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:44 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/26 19:44:40 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_pwd(void)
{
	char	buf[256];

	getcwd(buf, 256);
	ft_printf("%s\n", buf);
}

void	builtin_echo(t_token *token_lst)
{
	int		is_break_line;

	if (!token_lst || !token_lst->next)
	{
		ft_printf("\n");
		return ;
	}
	token_lst = token_lst->next;
	is_break_line = 1;
	if (ft_strcmp(token_lst->value, "-n") == 0)
	{
		token_lst = token_lst->next;
		is_break_line = 0;
	}
	while (token_lst)
	{
		ft_printf("%s ", token_lst->value);
		token_lst = token_lst->next;
	}
	if (is_break_line)
		ft_printf("\n");
}

void	builtin_env(t_env *env_lst)
{
	while (env_lst)
	{
		ft_printf("%s=%s\n",env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}
