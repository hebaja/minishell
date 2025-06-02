/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:44 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/02 19:50:42 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_cd(t_token *token_lst)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		return (1);
	ft_printf("%s\n", buf);
	if (chdir(token_lst->next->value) == -1)
		perror("chdir");
	return (0);
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		return (1);
	ft_printf("%s\n", buf);
	return (0);
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
