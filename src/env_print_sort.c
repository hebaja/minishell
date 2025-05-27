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

int	env_lst_size(t_env *lst)
{
	int count;

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

void	print_env_sort(t_env *lst)
{
	t_env	*start;
	t_env	*tmp;
	int		size;

	start = lst;
	size = env_lst_size(lst);
	if (!lst->next)
		return ;
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
		ft_printf("%s=%s\n",lst->key, lst->value);
		lst->printed = 1;
		lst = start;
		size--;
	}
	env_lst_iterate(lst, reset_env_printed);
}
