/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:46:31 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 19:46:36 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
		return (0);
	}
	return (1);
}

void	update_vars(t_env *env_lst, char *pwd, char *old_pwd)
{
	update_env_lst(pwd, env_lst);
	update_env_lst(old_pwd, env_lst);
	free(pwd);
	free(old_pwd);
}

int	cd_home(t_env *env_lst, char *buf)
{
	char	*home_path;
	char	*pwd;
	char	*old_pwd;

	home_path = get_var_value(env_lst, "HOME");
	if (!home_path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (0);
	}
	pwd = NULL;
	if (!change_dir(home_path))
		return (0);
	pwd = ft_strjoin("PWD=", home_path);
	old_pwd = ft_strjoin("OLDPWD=", buf);
	update_vars(env_lst, pwd, old_pwd);
	return (1);
}

int	cd_path(t_cmd *cmd_lst, t_env *env_lst, char *old_buf)
{
	char	new_buf[256];
	char	*pwd;
	char	*old_pwd;

	if (!change_dir(cmd_lst->args[1]))
		return (0);
	if (getcwd(new_buf, 256) == NULL)
	{
		perror("getcwd");
		cd_home(env_lst, get_var_value(env_lst, "PWD"));
		return (0);
	}
	pwd = ft_strjoin("PWD=", new_buf);
	old_pwd = ft_strjoin("OLDPWD=", old_buf);
	update_vars(env_lst, pwd, old_pwd);
	return (1);
}

int	builtin_cd(t_cmd *cmd_lst, t_env *env_lst)
{
	char	buf[256];

	getcwd(buf, 256);
	if (cmd_lst->args[0] && !cmd_lst->args[1])
	{
		if (!cd_home(env_lst, buf))
			return (BUILTIN_ERROR_STATUS);
	}
	else if (cmd_lst->args[0] && cmd_lst->args[1] && !cmd_lst->args[2])
	{
		if (!cd_path(cmd_lst, env_lst, buf))
			return (BUILTIN_ERROR_STATUS);
	}
	else
	{
		ft_putendl_fd("chdir: too many arguments", 2);
		return (BUILTIN_ERROR_STATUS);
	}
	return (BUILTIN_SUCCESS_STATUS);
}
