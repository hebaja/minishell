#include "minishell_test.h"

TestSuite(minishell_test_suite_cd, .init=init_test_redirect_stderr, .fini=clean_test);

Test(minishell_test_suite_cd, builtin_cd_1)
{
	char	*input = "cd";
	char	*old_pwd;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_null(ms->token_lst->next);
	old_pwd = ft_strdup(get_var_value(ms->env_lst, "PWD"));
	builtin_cd(ms->cmd_lst, ms->env_lst);
	cr_assert_str_eq(get_var_value(ms->env_lst, "HOME"), get_var_value(ms->env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(ms->env_lst, "OLDPWD"));
	free(old_pwd);
}

Test(minishell_test_suite_cd, builtin_cd_2)
{
	char	*input = "cd /home";
	char	*old_pwd;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_str_eq(ms->token_lst->next->value, "/home");
	old_pwd = ft_strdup(get_var_value(ms->env_lst, "PWD"));
	builtin_cd(ms->cmd_lst, ms->env_lst);
	cr_assert_str_eq("/home", get_var_value(ms->env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(ms->env_lst, "OLDPWD"));
	free(old_pwd);
}

Test(minishell_test_suite_cd, builtin_cd_3)
{
	char	*input = "cd directory";
	char	*pwd;
	char	*old_pwd;

	ms->input = input;
	ms->env_lst = build_envp();
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_str_eq(ms->token_lst->next->value, "directory");
	pwd = ft_strdup(get_var_value(ms->env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(ms->env_lst, "OLDPWD"));
	builtin_cd(ms->cmd_lst, ms->env_lst);
	cr_assert_str_eq(pwd, get_var_value(ms->env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(ms->env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
}

Test(minishell_test_suite_cd, builtin_cd_4)
{
	char	*input = "cd directory";
	char	*pwd;
	char	*old_pwd;

	ms->input = input;
	ms->env_lst = build_envp();
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_str_eq(ms->token_lst->next->value, "directory");
	pwd = ft_strdup(get_var_value(ms->env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(ms->env_lst, "OLDPWD"));
	mkdir("directory", 0200);
	builtin_cd(ms->cmd_lst, ms->env_lst);
	cr_assert_str_eq(pwd, get_var_value(ms->env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(ms->env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
	rmdir("directory");
}

Test(minishell_test_suite_cd, builtin_cd_5)
{
	char	*input = "cd file";
	char	*pwd;
	char	*old_pwd;

	ms->input = input;
	ms->env_lst = build_envp();
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_str_eq(ms->token_lst->next->value, "file");
	pwd = ft_strdup(get_var_value(ms->env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(ms->env_lst, "OLDPWD"));
	open("file", O_CREAT, 0644);
	builtin_cd(ms->cmd_lst, ms->env_lst);
	cr_assert_str_eq(pwd, get_var_value(ms->env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(ms->env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
	unlink("file");
}

Test(minishell_test_suite_cd, builtin_cd_6)
{
	char	*input = "cd /home /usr";
	char	*pwd;
	char	*old_pwd;

	ms->input = input;
	ms->env_lst = build_envp();
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_str_eq(ms->token_lst->next->value, "/home");
	cr_assert_str_eq(ms->token_lst->next->next->value, "/usr");
	pwd = ft_strdup(get_var_value(ms->env_lst, "PWD"));
	old_pwd = ft_strdup(get_var_value(ms->env_lst, "OLDPWD"));
	builtin_cd(ms->cmd_lst, ms->env_lst);
	cr_assert_str_eq(pwd, get_var_value(ms->env_lst, "PWD"));
	cr_assert_str_eq(old_pwd, get_var_value(ms->env_lst, "OLDPWD"));
	free(pwd);
	free(old_pwd);
}
