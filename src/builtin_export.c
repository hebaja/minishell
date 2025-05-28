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

int	create_new_node(t_env *env, char **var_val)
{
	t_env	*new_node;

	new_node =  malloc(sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE) ;
	new_node->key = ft_strdup(var_val[0]);
	new_node->value = ft_strdup(var_val[1]);
	new_node->printed = 0;
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
		return (0);
	ft_lstadd_back_env(&env, new_node);
	return (1);
}

int	add_to_env_lst(t_env *env_lst, char **var_val)
{
	env_lst_remove_if(&env_lst, var_val[0], compare);
	if (var_val[1])
	{
		if (!create_new_node(env_lst, var_val))
		{
			ft_putstr_fd("[Error]: The new_node failed\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else
		ft_printf("\n");
	return (EXIT_SUCCESS);
}

int	update_env_lst(char *value, t_env *env_lst)
{
	char	**var_val;

	var_val = ft_split(value, '=');
	if (add_to_env_lst(env_lst, var_val))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	builtin_export(t_token *token_lst, t_env *env_lst)
{
	if (!token_lst->next)
		print_env_sort(env_lst);
	else if (update_env_lst(token_lst->next->value, env_lst))
		return ;
}
