/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:49:07 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/26 19:20:45 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_env_node(t_env *env, char **var_val)
{
	t_env	*env_node;

	env_node =  malloc(sizeof(t_env));
	if (!env_node)
		return (0);
	env_node->key = ft_strdup(var_val[0]);
	env_node->value = ft_strdup(var_val[1]);
	env_node->printed = 0;
	env_node->next = NULL;
	if (!env_node->key || !env_node->value)
		return (0);
	ft_lstadd_back_env(&env, env_node);
	return (1);
}

void	add_to_env_lst(t_env *env_lst, char **var_val)
{
	env_lst_remove_if(&env_lst, var_val[0], compare);
	if (var_val[1])
	{
		if (!create_env_node(env_lst, var_val))
			ft_putstr_fd("Export failed\n", 2);
	}
	else
		ft_printf("\n");
}

void	clean_var_val(char **var_val)
{
	int		i;
	
	i = 0;
	while (var_val[i])
	{
		free(var_val[i]);
		i++;
	}
	free(var_val);
}

void	update_env_lst(char *value, t_env *env_lst)
{
	char	**var_val;

	var_val = ft_split(value, '=');
	add_to_env_lst(env_lst, var_val);
	clean_var_val(var_val);
}

void	builtin_export(t_token *token_lst, t_env *env_lst)
{
	if (!token_lst->next)
		print_env_sort(env_lst);
	else
		update_env_lst(token_lst->next->value, env_lst);
}
