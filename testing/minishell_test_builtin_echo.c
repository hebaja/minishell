#include "minishell_test.h"

TestSuite(minishell_test_suite_builtin_echo, .init=init_test_redirect_stdout, .fini=clean_test);

Test(minishell_test_suite_builtin_echo, build_token_lst_test_all_builtins_echo_mix)
{
	char	*input = "echo\'hello\'";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "echo\'hello\'");
	cr_assert_null(ms->token_lst->next);
}
 
Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_echo)
{
	char	*input = "echo -n Hello";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_echo_raw)
{
	char	*input = "echo";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("\n");
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_echo_sd_nobr)
{
	char	*input = "echo -n Hello";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("Hello");
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_echo_br)
{
	char	*input = "echo Hello";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("Hello\n");
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_multi)
{
	char	*input = "echo Hello Hi Hey";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi Hey\n");
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_space)
{
	char	*input = "echo Hello         Hi";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi\n");
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_multi_nobr)
{
	char	*input = "echo -n Hello Hi";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi");
}

Test(minishell_test_suite_builtin_echo, build_token_lst_test_builtin_multi_nobr_space)
{
	char	*input = "echo -n Hello        Hi";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_echo(ms->cmd_lst);
	test_lst(ms->token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi");
}
