/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:41:03 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/15 20:16:12 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char *key, char *variable)
{
	return (ft_strcmp(key, variable) == 0);
}

int	ascending(char *a, char *b)
{
	return (ft_strcmp(a, b) <= 0);
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

t_env	*ft_sort_list(t_env *lst, int (*cmp)())
{
	t_env	*start;
	char	*tmp_key;
	char	*tmp_value;

	start = lst;
	if (!lst->next)
		return (lst);
	while (lst->next)
	{
		if (!(cmp)(lst->key, lst->next->key))
		{
			tmp_key = lst->key;
			lst->key = lst->next->key;
			lst->next->key = tmp_key;
			tmp_value = lst->value;
			lst->value = lst->next->value;
			lst->next->value = tmp_value;
			lst = start;
		}
		else
			lst = lst->next;
	}
	return (lst);
}
