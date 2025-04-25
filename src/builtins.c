/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:44 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/24 18:08:02 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_cd(t_token *token_lst)
{
	char	buf[100];

	getcwd(buf, 100);
	ft_printf("%s\n", buf);
	if (chdir(token_lst->next->value) == -1)
		perror("chdir");
}

void	builtin_pwd(void)
{
	char	buf[100];

	getcwd(buf, 100);
	ft_printf("%s\n", buf);
}

void	builtin_echo(t_token *token_lst)
{
	t_token *current;

	current = token_lst->next;
	if (ft_strcmp(current->value, "-n") == 0)
	{
		if (current->next->type == WORD)
			ft_printf("%s", token_lst->next->next->value);
		return ;
	}
	else if (current->type == WORD)
	{
		ft_printf("%s\n", token_lst->next->value);
		return ;
	}
	else
		ft_printf("\n");
}
