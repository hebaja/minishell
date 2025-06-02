#include "../include/minishell.h"

int	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
		ft_putstr_fd("chdir failed\n", 2);
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

void	builtin_cd(t_token *token_lst, t_env *env_lst)
{
	char	buf[256];
	char	*home_path;
	char	*pwd;
	char	*old_pwd;

	getcwd(buf, 256);
	pwd = NULL;
	old_pwd = ft_strjoin("OLDPWD=", buf);
	if (!token_lst->next)
	{
		home_path = get_var_value(env_lst, "HOME");
		if (!change_dir(home_path))
			return ;
		pwd = ft_strjoin("PWD=", home_path);
	}
	else
	{
		if (!change_dir(token_lst->next->value))
			return ;
		getcwd(buf, 256);
		pwd = ft_strjoin("PWD=", buf);
	}
	update_vars(env_lst, pwd, old_pwd);
}
