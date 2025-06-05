#include "minishell_test.h"

Test(minishell_test_suite_exit, test_exit_42, .exit_code = 42, .fini=clean_test)
{
	char	*input = "exit 42";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_exit(&token_lst, &env_lst);
}

Test(minishell_test_suite_exit, test_exit_1, .exit_code = 1)
{
	char	*input = "exit 1";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_exit(&token_lst, &env_lst);
}

Test(minishell_test_suite_exit, test_exit_0, .exit_code = 0)
{
	char	*input = "exit 0";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	builtin_exit(&token_lst, &env_lst);
}
