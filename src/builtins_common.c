/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:44 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/26 19:44:40 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

int	exec_builtin(t_cmd *cmd, t_env *env_lst)
{
	int	status;

	status = 0;
	if (cmd->main_type == BUILTIN_ECHO)
		status = builtin_echo(cmd);
	if (cmd->main_type == BUILTIN_ENV)
		status = builtin_env(env_lst);
	if (cmd->main_type == BUILTIN_CD)
		status = builtin_cd(cmd, env_lst);
	if (cmd->main_type == BUILTIN_PWD)
		status = builtin_pwd();
	if (cmd->main_type == BUILTIN_EXPORT)
		status = builtin_export(cmd, env_lst);
	if (cmd->main_type == BUILTIN_UNSET)
		status = builtin_unset(cmd, &env_lst);
	if (cmd->main_type == BUILTIN_EXIT)
		status = builtin_exit(cmd);
	return (status);
}

int	is_builtin(t_token_type type)
{
	if (type == BUILTIN_ECHO
	|| type == BUILTIN_ENV
	|| type == BUILTIN_CD
	|| type == BUILTIN_PWD
	|| type == BUILTIN_EXPORT
	|| type == BUILTIN_UNSET
	|| type == BUILTIN_EXIT)
		return (1);
	return (0);
}

int	builtin_pwd(void)
{
	char	buf[256];

	if (getcwd(buf, 256) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%s\n", buf);
	return (0);
}

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		is_break_line;

	if (!cmd->args[0] || !cmd->args[1])
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	is_break_line = 1;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		is_break_line = 0;
		i = 2;
	}
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (is_break_line)
		ft_printf("\n");
	return (0);
}

int	builtin_env(t_env *env_lst)
{
	while (env_lst)
	{
		ft_printf("%s=%s\n",env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
}
