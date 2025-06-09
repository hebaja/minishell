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

int	cd_home(t_env *env_lst, char **pwd)
{
	char	*home_path;

	home_path = get_var_value(env_lst, "HOME");
	if (!change_dir(home_path))
		return (0);
	*pwd = ft_strjoin("PWD=", home_path);
	return (1);
}

int	cd_path(char *path, char **pwd)
{
	char	buf[256];

	if (!change_dir(path))
		return (0);
	getcwd(buf, 256);
	*pwd = ft_strjoin("PWD=", buf);
	return (1);
}

int	builtin_cd(t_cmd *cmd_lst, t_env *env_lst)
{
	char	buf[256];
	char	*pwd;
	char	*old_pwd;

	getcwd(buf, 256);
	pwd = NULL;
	old_pwd = ft_strjoin("OLDPWD=", buf);
	if (cmd_lst->args[0] && !cmd_lst->args[1])
	{
		if (!cd_home(env_lst, &pwd))
			return (1);
	}
	else if (cmd_lst->args[0] && cmd_lst->args[1] && !cmd_lst->args[2])
	{
		if (!cd_path(cmd_lst->args[1], &pwd))
			return (1);
	}
	else
	{
		ft_putstr_fd("chdir: too many arguments\n", 2);
		return (1);
	}
	update_vars(env_lst, pwd, old_pwd);
	return (0);
}
