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

void	builtin_cd(t_token *token_lst)
{
	char	buf[300];

	getcwd(buf, 300);
	ft_printf("%s\n", buf);
	if (chdir(token_lst->next->value) == -1)
		perror("chdir");
}

void	builtin_pwd(void)
{
	char	buf[300];

	getcwd(buf, 300);
	ft_printf("%s\n", buf);
}

void	builtin_echo(t_token *token_lst)
{
	t_token *current;

	if (!token_lst || !token_lst->next)
	{
		ft_printf("\n");
		return ;
	}
	current = token_lst->next;
	if (ft_strcmp(current->value, "-n") == 0)
	{
		while (current->next->type == WORD)
		{
			ft_printf("%s ", current->next->value);
			if (current->next == NULL)
				return ;
			current = current->next;
		}
	}
	else if (current->type == WORD)
	{
		while (current->value)
		{
			ft_printf("%s ", current->value);
			if (current->next == NULL)
			{
				ft_printf("\n");	
				return ;
			}
			current = current->next;
		}
		return ;
	}
	else
		ft_printf("\n");
}

void	builtin_env(t_env *env_head)
{
	t_env	*temp;

	temp = env_head;
	while (temp)
	{
		ft_printf("%s=%s\n",temp->key, temp->value);
		temp = temp->next;
	}
}
