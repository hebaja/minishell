#include "minishell_test.h"

Test(minishell_test_suite_exit, test_exit_42, .init=init_test, .fini=clean_test)
{
	char	*input = "exit 42";
	int		return_value;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	return_value = builtin_exit(ms->cmd_lst, ms->status);
	cr_assert_eq(return_value, 42);
}

Test(minishell_test_suite_exit, test_exit_1, .init=init_test, .fini=clean_test)
{
	char	*input = "exit 1";
	int		return_value;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	return_value = builtin_exit(ms->cmd_lst, ms->status);
	cr_assert_eq(return_value, 1);
}

Test(minishell_test_suite_exit, test_exit_0, .init=init_test, .fini=clean_test)
{
	char	*input = "exit 0";
	int		return_value;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	return_value = builtin_exit(ms->cmd_lst, ms->status);
	cr_assert_eq(return_value, 0);
}
