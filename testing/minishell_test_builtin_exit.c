#include "minishell_test.h"

Test(minishell_test_suite_exit, test_exit_42, .init=init_test, .exit_code = 42, .fini=clean_test)
{
	char	*input = "exit 42";

	res = token_lst_build(ms, input);
	cr_assert_eq(res, 1);
	usual_flow(ms, input);
	builtin_exit(ms->cmd_lst);
	ft_printf("--> %s\n", ms->cmd_lst->args[0]);
	ft_printf("--> %s\n", ms->cmd_lst->args[1]);
}

Test(minishell_test_suite_exit, test_exit_1, .init=init_test, .exit_code = 1, .fini=clean_test)
{
	char	*input = "exit 1";

	res = token_lst_build(ms, input);
	cr_assert_eq(res, 1);
	usual_flow(ms, input);
	builtin_exit(ms->cmd_lst);
}

/*
Test(minishell_test_suite_exit, test_exit_0, .exit_code = 0)
{
	char	*input = "exit 0";

	res = token_lst_build(ms, input);
	cr_assert_eq(res, 1);
	usual_flow(ms, input);
	builtin_exit(ms->cmd_lst);
}
*/
