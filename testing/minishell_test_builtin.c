#include "criterion-2.4.2/include/criterion/assert.h"
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
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_cd_mix)
{
	char	*input = "cd\"hello\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "cd\"hello\"");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_pwd_mix)
{
	char	*input = "pwd\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "pwd\'hello\'");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_export_mix)
{
	char	*input = "export\"hello\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "export\"hello\"");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_unset_mix)
{
	char	*input = "unset\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "unset\'hello\'");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_env_mix)
{
	char	*input = "env\"hello\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "env\"hello\"");
}

Test(minishell_test_suite_builtin, build_token_lst_test_all_builtins_exit_mix)
{
	char	*input = "exit\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "exit\'hello\'");
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
