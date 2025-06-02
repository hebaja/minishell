#include "minishell_test.h"

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins)
{
	char	*input = "echo cd pwd export unset env exit";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_not)
{
	char	*input = "echoa cda pwda exporta unseta enva exita";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_echo_mix)
{
	char	*input = "echo\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "echo\'hello\'");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_cd_mix)
{
	char	*input = "cd\"hello\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "cd\"hello\"");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_pwd_mix)
{
	char	*input = "pwd\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "pwd\'hello\'");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_export_mix)
{
	char	*input = "export\"hello\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "export\"hello\"");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_unset_mix)
{
	char	*input = "unset\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "unset\'hello\'");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_env_mix)
{
	char	*input = "env\"hello\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "env\"hello\"");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_exit_mix)
{
	char	*input = "exit\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "exit\'hello\'");
	cr_assert_null(token_lst->next);
}
 
Test(minishell_test_suite_builtin, build_token_lst_test_builtin_echo)
{
	char	*input = "echo -n Hello";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_test_builting_cd)
{
	char	*input = "cd /home/user/folder";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_pwd)
{
	char	*input = "pwd";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_export)
{
	char	*input = "export VARIABLE=VALUE";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_unset)
{
	char	*input = "unset VARIABLE";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_env)
{
	char	*input = "env";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_exit)
{
	char	*input = "exit";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_mixed)
{
	char	*input = "echo >> doc || cat --abord < ls -l";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_mixed_2)
{
	char	*input = "echo>>doc || less<more";

	values = populate_values(7, "echo", ">>", "doc", "||", "less", "<", "more");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_1)
{
	t_env	*env_lst;
	char	*input = "ec\"ho\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "ec\"ho\"");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "echo");
	cr_assert_eq(token_lst->type, BUILTIN_ECHO);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_2)
{
	t_env	*env_lst;
	char	*input = "p\'wd\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "p\'wd\'");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "pwd");
	cr_assert_eq(token_lst->type, BUILTIN_PWD);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_3)
{
	t_env	*env_lst;
	char	*input = "c\"d\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "c\"d\"");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "cd");
	cr_assert_eq(token_lst->type, BUILTIN_CD);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_4)
{
	t_env	*env_lst;
	char	*input = "exp\'ort\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "exp\'ort\'");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "export");
	cr_assert_eq(token_lst->type, BUILTIN_EXPORT);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_5)
{
	t_env	*env_lst;
	char	*input = "un\"set\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "un\"set\"");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "unset");
	cr_assert_eq(token_lst->type, BUILTIN_UNSET);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_6)
{
	t_env	*env_lst;
	char	*input = "en\'v\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "en\'v\'");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "env");
	cr_assert_eq(token_lst->type, BUILTIN_ENV);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_7)
{
	t_env	*env_lst;
	char	*input = "exi\"t\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "exi\"t\"");
	cr_assert_eq(token_lst->type, WORD);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "exit");
	cr_assert_eq(token_lst->type, BUILTIN_EXIT);
}

Test(minishell_test_suite_builtin, build_token_lst_builtin_recheck_all)
{
	t_env	*env_lst;
	char	*input = "ec\"ho\" \'c\'d pw\"d\" exp\'ort\' un\"set\" en\'v\' ex\"it\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	values = populate_values(7, "echo", "cd", "pwd", "export", "unset", "env", "exit");
	types = fetch_tokens_type_list(token_lst);
	test_lst(token_lst, values, types);
}
