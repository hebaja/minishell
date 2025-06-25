#include "minishell_test.h"

Test(minishell_test_suite_unset, test_unset, .init=init_test, .fini=clean_test)
{
	char	*input = "unset LANGUAGE";
	char	*var_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	builtin_unset(ms->cmd_lst, &ms->env_lst);
	var_value = get_var_value(ms->env_lst, "LANGUAGE");
	cr_assert_null(var_value);
}

Test(minishell_test_suite_unset, test_unset_create, .init=init_test, .fini=clean_test)
{
	char	*input = "export TEST=test";
	char	*var_value;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	builtin_export(ms->cmd_lst, ms->env_lst);
	var_value = get_var_value(ms->env_lst, "TEST");
	cr_assert_str_eq(var_value, "test");
	ms->token_lst = NULL;
	ms->cmd_lst = NULL;
	ms->input = NULL;
	ms->input = "unset TEST";
	var_value = NULL;
	token_lst_build(ms);
	usual_flow(ms);
	builtin_unset(ms->cmd_lst, &ms->env_lst);
	var_value = get_var_value(ms->env_lst, "TEST");
	cr_assert_null(var_value);
}
