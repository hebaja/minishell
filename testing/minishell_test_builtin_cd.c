#include "minishell_test.h"

TestSuite(minishell_test_suite_cd, .init=redirect_stdout_err);

Test(minishell_test_suite_cd, builtin_cd_1)
{
	t_env	*env_lst;
	char	*input = "cd";
	char	*old_pwd;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_null(token_lst->next);
	old_pwd = ft_strdup(get_var_value(env_lst, "PWD"));
	builtin_cd(token_lst, env_lst);
	cr_assert_str_eq(get_var_value(env_lst, "HOME"), get_var_value(env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(env_lst, "OLDPWD"));
	free(old_pwd);
}

Test(minishell_test_suite_cd, builtin_cd_2)
{
	t_env	*env_lst;
	char	*input = "cd /home";
	char	*old_pwd;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_str_eq(token_lst->next->value, "/home");
	old_pwd = ft_strdup(get_var_value(env_lst, "PWD"));
	builtin_cd(token_lst, env_lst);
	cr_assert_str_eq("/home", get_var_value(env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(env_lst, "OLDPWD"));
	free(old_pwd);
}

Test(minishell_test_suite_cd, builtin_cd_3)
{
	t_env	*env_lst;
	char	*input = "cd directory";
	char	*pwd;
	char	*old_pwd;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_str_eq(token_lst->next->value, "directory");
	pwd = ft_strdup(get_var_value(env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(env_lst, "OLDPWD"));
	builtin_cd(token_lst, env_lst);
	cr_assert_str_eq(pwd, get_var_value(env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
}

Test(minishell_test_suite_cd, builtin_cd_4)
{
	t_env	*env_lst;
	char	*input = "cd directory";
	char	*pwd;
	char	*old_pwd;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_str_eq(token_lst->next->value, "directory");
	pwd = ft_strdup(get_var_value(env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(env_lst, "OLDPWD"));
	mkdir("directory", 0200);
	builtin_cd(token_lst, env_lst);
	cr_assert_str_eq(pwd, get_var_value(env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
	rmdir("directory");
}

Test(minishell_test_suite_cd, builtin_cd_5)
{
	t_env	*env_lst;
	char	*input = "cd file";
	char	*pwd;
	char	*old_pwd;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_str_eq(token_lst->next->value, "file");
	pwd = ft_strdup(get_var_value(env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(env_lst, "OLDPWD"));
	open("file", O_CREAT, 0644);
	builtin_cd(token_lst, env_lst);
	cr_assert_str_eq(pwd, get_var_value(env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
	unlink("file");
}

Test(minishell_test_suite_cd, builtin_cd_6)
{
	t_env	*env_lst;
	char	*input = "cd /home /usr";
	char	*pwd;
	char	*old_pwd;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_str_eq(token_lst->next->value, "/home");
	cr_assert_str_eq(token_lst->next->next->value, "/usr");
	pwd = ft_strdup(get_var_value(env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(env_lst, "OLDPWD"));
	builtin_cd(token_lst, env_lst);
	cr_assert_str_eq(pwd, get_var_value(env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
}
