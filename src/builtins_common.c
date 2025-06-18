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

void	close_redirect_fds(t_cmd *cmd)
{
	if (cmd->fd_out > 2)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	if (cmd->fd_in > 2)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
}

int	exec_builtin(t_cmd *cmd, t_ms *ms)
{
	int	status;

	status = 0;
	if (cmd->main_type == BUILTIN_ECHO)
		status = builtin_echo(cmd);
	if (cmd->main_type == BUILTIN_ENV)
		status = builtin_env(ms->env_lst, cmd);
	if (cmd->main_type == BUILTIN_CD)
		status = builtin_cd(cmd, ms->env_lst);
	if (cmd->main_type == BUILTIN_PWD)
		status = builtin_pwd(cmd);
	if (cmd->main_type == BUILTIN_EXPORT)
		status = builtin_export(cmd, ms->env_lst);
	if (cmd->main_type == BUILTIN_UNSET)
		status = builtin_unset(cmd, &ms->env_lst);
	if (cmd->main_type == BUILTIN_EXIT)
		status = builtin_exit(cmd, ms->status);
	close_redirect_fds(cmd);
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

int	builtin_pwd(t_cmd *cmd_lst)
{
	char	buf[256];

	if (getcwd(buf, 256) == NULL)
	{
		perror("getcwd");
		return (BUILTIN_ERROR_STATUS);
	}
	ft_putstr_fd(buf, cmd_lst->fd_out);
	ft_putstr_fd("\n", cmd_lst->fd_out);
	return (BUILTIN_SUCCESS_STATUS);
}

int	builtin_env(t_env *env_lst, t_cmd *cmd)
{
	while (env_lst)
	{
		print_env(env_lst, cmd);
		env_lst = env_lst->next;
	}
	return (BUILTIN_SUCCESS_STATUS);
}
