/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:34:29 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 20:34:31 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp_key_str(char *key, char *variable)
{
	return (ft_strcmp(key, variable) == 0);
}

void	env_clear(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
	env = NULL;
}

void	env_lst_clear(t_env **env_lst)
{
	if (env_lst != NULL)
		env_lst_iterate(*env_lst, env_clear);
	*env_lst = NULL;
}

char	*get_var_value(t_env *env_lst, char *var_key)
{
	while (env_lst)
	{
		if (cmp_key_str(env_lst->key, var_key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	env_lst_remove_if(t_env **env, char *key,
	int cmp(char *s1, char *s2))
{
	t_env	*current;
	t_env	*tmp;

	if (!env || !*env || !key)
		return ;
	current = *env;
	if (cmp(current->key, key))
	{
		tmp = current;
		*env = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		env_lst_remove_if(env, key, cmp);
	}
	else
		env_lst_remove_if(&current->next, key, cmp);
}
