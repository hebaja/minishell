#include "minishell_test.h"

Test(minishell_test_suite_unset, test_unset)
{
	char	*input = "unset LANGUAGE";
	char	*var_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_unset(token_lst, &env_lst);
	var_value = get_var_value(env_lst, "LANGUAGE");
	cr_assert_null(var_value);
}

Test(minishell_test_suite_unset, test_unset_create, .init=redirect_stdout)
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
	token_lst = NULL;
	free(var_value);
	var_value = NULL;
	token_lst_build(&token_lst, "unset TEST");
	usual_flow(&token_lst, env_lst);
	builtin_export(token_lst, env_lst);
	var_value = get_var_value(env_lst, "TEST");
	cr_assert_null(var_value);
}
