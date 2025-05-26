/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:41:03 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/19 19:43:59 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char *key, char *variable)
{
	return (ft_strcmp(key, variable) == 0);
}

void	ft_list_remove_if(t_env **env, t_token *variable , int (*cmp)())
{
	t_env	*current;
	t_env	*tmp;

	if (!env || !*env || !variable)
		return ;
	current = *env;
	if (cmp(current->key, variable->next->value))
	{
		tmp = current;
		*env = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		ft_list_remove_if(env, variable, cmp);
	}
	else
		ft_list_remove_if(&current->next, variable, cmp);
}

int	ft_list_size(t_env *lst)
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

void	env_iter(t_env *lst_env, void (*f)())
{
	if (!lst_env)
		return ;
	while (lst_env)
	{
		(f)(lst_env);
		lst_env = lst_env->next;
	}
}

void	ft_printed(t_env *lst)
{
	t_env	*start;
	t_env	*tmp;
	int		size;

	start = lst;
	size = ft_list_size(lst);
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
	env_iter(lst, reset_env_printed);
}
