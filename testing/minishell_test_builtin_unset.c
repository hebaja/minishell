#include "minishell_test.h"

Test(minishell_test_suite_unset, test_unset, .init=init_test, .fini=clean_test)
{
	char	*input = "unset LANGUAGE";
	char	*var_value;

	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms, input);
	builtin_unset(ms->cmd_lst, &ms->env_lst);
	var_value = get_var_value(ms->env_lst, "LANGUAGE");
	cr_assert_null(var_value);
}

/*
Test(minishell_test_suite_unset, test_unset_create, .init=redirect_stdout, .fini=clean_test)
{
	char	*input = "export TEST=test";
	char	*var_value;

	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value = get_var_value(env_lst, "TEST");
	cr_assert_str_eq(var_value, "test");
	token_lst = NULL;
	var_value = NULL;
	token_lst_build(ms, "unset TEST");
	usual_flow(ms);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value = get_var_value(env_lst, "TEST");
	cr_assert_null(var_value);
}
*/
