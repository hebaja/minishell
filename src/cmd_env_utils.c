/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:20:00 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 20:20:03 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*build_env_sp(t_env *env)
{
	char	*env_str;
	size_t	env_size;
	size_t	key_size;
	size_t	val_size;

	key_size = ft_strlen(env->key);
	val_size = ft_strlen(env->value);
	env_size = key_size + val_size + 2;
	env_str = ft_calloc(sizeof(char), env_size);
	ft_memmove(env_str, env->key, key_size);
	ft_memmove(&env_str[key_size], "=", 1);
	ft_memmove(&env_str[key_size + 1], env->value, val_size);
	return (env_str);
}

char	**split_env(t_env *env_lst)
{
	int		i;
	char	**env_sp;
	size_t	size;

	i = 0;
	size = env_lst_size(env_lst);
	env_sp = (char **)malloc(sizeof(char *) * (size + 1));
	while (env_lst)
	{
		env_sp[i] = build_env_sp(env_lst);
		env_lst = env_lst->next;
		i++;
	}
	env_sp[i] = NULL;
	return (env_sp);
}
