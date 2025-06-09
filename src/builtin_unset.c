/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:14 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/26 18:48:33 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	builtin_unset(t_cmd *cmd_lst, t_env **env_lst)
{
	if (cmd_lst->args[1]
		&& get_var_value(*env_lst, cmd_lst->args[1]) != NULL)
		env_lst_remove_if(env_lst, cmd_lst->args[1], compare);
	return (1);
}
