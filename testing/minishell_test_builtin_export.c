#include "minishell_test.h"

Test(minishell_test_suite_export, test_export)
{
	char	*input = "export TEST=test";
	char	*var_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_export(token_lst, env_lst);
	var_value = get_var_value(env_lst, "TEST");
	cr_assert_str_eq(var_value, "test");
}

Test(minishell_test_suite_export, test_export_change)
{
	char	*input = "export TEST=test";
	char	*var_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_export(token_lst, env_lst);
	var_value = get_var_value(env_lst, "TEST");
	cr_assert_str_eq(var_value, "test");

	char	*input_2 = "export TEST=change";
	char	*var_value_2;
	t_token	*token;
	token_lst_build(&token, input_2);
	usual_flow(&token, env_lst);
	builtin_export(token, env_lst);
	var_value_2 = get_var_value(env_lst, "TEST");
	cr_assert_str_eq(var_value_2, "change");
}

/*
Test(minishell_test_suite_export, test_export_change_exist)
{
	t_env	*env_lst;
	char	*input = "export LANGUAGE=pt";
	char	*var_value;

	env_lst = build_envp();                                                  
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq("en", get_var_value(env_lst, "LANGUAGE"));
	usual_flow(&token_lst, env_lst);
	builtin_export(token_lst, env_lst);
	var_value = get_var_value(env_lst, "LANGUAGE");
	cr_assert_str_eq(var_value, "pt");
}
*/
