/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:41:03 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/26 18:33:51 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(t_env *env_lst, t_cmd *cmd)
{
	ft_putstr_fd(env_lst->key, cmd->fd_out);
	ft_putstr_fd("=", cmd->fd_out);
	ft_putendl_fd(env_lst->value, cmd->fd_out);
}

int	env_lst_size(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	reset_env_printed(t_env *env_lst)
{
	env_lst->printed = 0;
}

/*
 * TODO function removed from line 13. Check if necessary
	if (!lst->next)
		return ;
*/	

void	print_env_sort(t_env *lst, t_cmd *cmd)
{
	t_env	*start;
	t_env	*tmp;
	int		size;

	start = lst;
	size = env_lst_size(lst);
	while (size)
	{
		while (lst->printed == 1)
			lst = lst->next;
		tmp = lst->next;
		while (tmp)
		{
			if (ft_strcmp(lst->key, tmp->key) > 0 && tmp->printed == 0)
				lst = tmp;
			tmp = tmp->next;
		}
		print_env(lst, cmd);
		lst->printed = 1;
		lst = start;
		size--;
	}
	env_lst_iterate(lst, reset_env_printed);
}
