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

int	update_env_lst(char *value, t_env *env_lst)
{
	int		i;
	char	**var_val;

	i = -1;
	var_val = ft_split(value, '=');
	while (var_val[0][++i])
	{
		if ((i == 0 && (!ft_isalpha(var_val[0][0]) && var_val[0][0] != '_'))
			|| (i != 0 && (!ft_isalnum(var_val[0][i]) && var_val[0][i] != '_')))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			return (0);
		}
	}
	add_to_env_lst(env_lst, var_val);
	clean_var_val(var_val);
	return (1);
}

int	builtin_export(t_cmd *cmd_lst, t_env *env_lst)
{
	if (!cmd_lst->args[1])
		print_env_sort(env_lst);
	else
		if (!update_env_lst(cmd_lst->args[1], env_lst))
			return (1);
	return (0);
}
