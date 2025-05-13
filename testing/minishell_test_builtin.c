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
