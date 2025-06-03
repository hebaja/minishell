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

int	cd_path(t_token *token_lst, char **pwd)
{
	char	buf[256];

	if (!change_dir(token_lst->next->value))
		return (0);
	getcwd(buf, 256);
	*pwd = ft_strjoin("PWD=", buf);
	return (1);
}

void	builtin_cd(t_token *token_lst, t_env *env_lst)
{
	char	buf[256];
	char	*pwd;
	char	*old_pwd;

	getcwd(buf, 256);
	pwd = NULL;
	old_pwd = ft_strjoin("OLDPWD=", buf);
	if (token_lst->value && !token_lst->next)
	{
		if (!cd_home(env_lst, &pwd))
			return ;
	}
	else if (token_lst->value && token_lst->next->value
		&& !token_lst->next->next)
	{
		if (!cd_path(token_lst, &pwd))
			return ;
	}
	else
	{
		ft_putstr_fd("chdir: too many arguments\n", 2);
		return ;
	}
	update_vars(env_lst, pwd, old_pwd);
}
