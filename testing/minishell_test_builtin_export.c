#include "minishell_test.h"

TestSuite(minishell_test_suite_export, .init=init_test, .fini=clean_test);

Test(minishell_test_suite_export, test_export)
{
	char	*input = "export TEST=test";
	char	*var_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value = get_var_value(ms->env_lst, "TEST");
	cr_assert_str_eq(var_value, "test");
}


Test(minishell_test_suite_export, test_export_change)
{
	char	*input = "export TEST=test";
	char	*var_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value = get_var_value(ms->env_lst, "TEST");
	cr_assert_str_eq(var_value, "test");
	char	*input_2 = "export TEST=change";
	char	*var_value_2;
	ms->token_lst = NULL;
	ms->cmd_lst = NULL;
	ms->input = NULL;
	ms->input = input_2;
	token_lst_build(ms);
	usual_flow(ms);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value_2 = get_var_value(ms->env_lst, "TEST");
	cr_assert_str_eq(var_value_2, "change");
}

Test(minishell_test_suite_export, test_export_change_exist)
{
	char	*input = "export LANGUAGE=pt";
	char	*var_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	var_value = get_var_value(ms->env_lst, "LANGUAGE");
	cr_assert_str_eq(var_value, "en");
	var_value = NULL;
	usual_flow(ms);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value = get_var_value(ms->env_lst, "LANGUAGE");
	cr_assert_str_eq(var_value, "pt");
}
