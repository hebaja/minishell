#include "minishell_test.h"

TestSuite(minishell_test_suite_echo_redirect, .init=redirect_stdout, .fini=clean_test);

Test(minishell_test_suite_echo_redirect, build_token_lst_test_all_builtins_echo_mix)
{
	char	*input = "echo\'hello\'";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "echo\'hello\'");
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

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_echo)
{
	t_env	*env_lst;
	char	*input = "echo";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("\n");
}

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_echo_sd_nobr)
{
	t_env	*env_lst;
	char	*input = "echo -n Hello";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("Hello");
}

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_echo_br)
{
	t_env	*env_lst;
	char	*input = "echo Hello";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("Hello\n");
}

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_multi)
{
	t_env	*env_lst;
	char	*input = "echo Hello Hi Hey";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi Hey\n");
}

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_space)
{
	t_env	*env_lst;
	char	*input = "echo Hello         Hi";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi\n");
}

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_multi_nobr)
{
	t_env	*env_lst;
	char	*input = "echo -n Hello Hi";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi");
}

Test(minishell_test_suite_echo_redirect, build_token_lst_test_builtin_multi_nobr_space)
{
	t_env	*env_lst;
	char	*input = "echo -n Hello        Hi";
	
	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_echo(token_lst);
	test_lst(token_lst, values, types);
	cr_assert_stdout_eq_str("Hello Hi");
}
