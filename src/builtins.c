/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:32:10 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/09 19:21:37 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void fn_echo(t_token *token_lst)
{
	t_token *current;
	
	if (!token_lst || !token_lst->next)
	{
		ft_printf("\n");
		return ;
	}
	current = token_lst->next;
	while (current)
	{
		if (ft_strcmp(current->value, "-n") == 0)
		{	
			if (!current->next || !current)
				return ;
			else if (current->next->type == WORD)
			{
				ft_printf("%s",current->next->value);
				return ;
			}
		}
		else if (current->type == WORD)
			ft_printf("%s\n", current->value);
		current = current->next;
	}
}

void	fn_cd(char *path)
{
	char	buf[100];

	getcwd(buf, 100);
	if (chdir(path) == -1)
		perror("chdir");
}

void	fn_pwd(void)
{	
	char	buf[100];

	getcwd(buf, 100);
	ft_printf("%s\n", buf);
}

void	builts(t_token *token_lst)
{
	if (ft_strncmp(token_lst->value ,"echo", 5) == 0)
		fn_echo(token_lst);
	else if (ft_strncmp(token_lst->value ,"pwd", 4) == 0)
		fn_pwd();
	else if (ft_strncmp(token_lst->value ,"cd", 3) == 0)
		fn_cd(token_lst->next->value);
}




