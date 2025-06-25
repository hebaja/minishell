#include "minishell_test.h"

TestSuite(minishell_test_suite_builtin, .init=init_test, .fini=clean_test);

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins)
{
	char	*input = "echo cd pwd export unset env exit";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_not)
{
	char	*input = "echoa cda pwda exporta unseta enva exita";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_cd_mix)
{
	char	*input = "cd\"hello\"";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "cd\"hello\"");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_pwd, .init=redirect_stdout)
{
	char	*input = "pwd";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "pwd");
	cr_assert_null(ms->token_lst->next);
	usual_flow(ms);
	chdir("/home");
	builtin_pwd(ms->cmd_lst);
	cr_assert_stdout_eq_str("/home\n");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_pwd_more, .init=redirect_stdout)
{
	char	*input = "pwd more";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "pwd");
	usual_flow(ms);
	chdir("/home");
	builtin_pwd(ms->cmd_lst);
	cr_assert_stdout_eq_str("/home\n");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_pwd_mix)
{
	char	*input = "pwd\'hello\'";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "pwd\'hello\'");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_export_mix)
{
	char	*input = "export\"hello\"";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "export\"hello\"");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_unset_mix)
{
	char	*input = "unset\'hello\'";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "unset\'hello\'");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_env_mix)
{
	char	*input = "env\"hello\"";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "env\"hello\"");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_exit_mix)
{
	char	*input = "exit\'hello\'";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "exit\'hello\'");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_builting_cd)
{
	char	*input = "cd /home/user/folder";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_pwd)
{
	char	*input = "pwd";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_export)
{
	char	*input = "export VARIABLE=VALUE";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_unset)
{
	char	*input = "unset VARIABLE";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_env)
{
	char	*input = "env";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_exit)
{
	char	*input = "exit";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_mixed)
{
	char	*input = "echo > doc | cat --abord < ls -l";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_mixed_2)
{
	char	*input = "echo>>doc | less<more";

	ms->input = input;
	values = populate_values(7, "echo", ">>", "doc", "|", "less", "<", "more");
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_1)
{
	char	*input = "ec\"ho\"";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "ec\"ho\"");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "echo");
	cr_assert_eq(ms->token_lst->type, BUILTIN_ECHO);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_2)
{
	char	*input = "p\'wd\'";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "p\'wd\'");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "pwd");
	cr_assert_eq(ms->token_lst->type, BUILTIN_PWD);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_3)
{
	char	*input = "c\"d\"";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "c\"d\"");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "cd");
	cr_assert_eq(ms->token_lst->type, BUILTIN_CD);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_4)
{
	char	*input = "exp\'ort\'";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "exp\'ort\'");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "export");
	cr_assert_eq(ms->token_lst->type, BUILTIN_EXPORT);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_5)
{
	char	*input = "un\"set\"";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "un\"set\"");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "unset");
	cr_assert_eq(ms->token_lst->type, BUILTIN_UNSET);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_6)
{
	char	*input = "en\'v\'";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "en\'v\'");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "env");
	cr_assert_eq(ms->token_lst->type, BUILTIN_ENV);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_7)
{
	char	*input = "exi\"t\"";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "exi\"t\"");
	cr_assert_eq(ms->token_lst->type, WORD);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "exit");
	cr_assert_eq(ms->token_lst->type, BUILTIN_EXIT);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_all)
{
	char	*input = "ec\"ho\" \'c\'d pw\"d\" exp\'ort\' un\"set\" en\'v\' ex\"it\"";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	values = populate_values(7, "echo", "cd", "pwd", "export", "unset", "env", "exit");
	types = fetch_tokens_type_list(ms->token_lst);
	test_lst(ms->token_lst, values, types);
}
