#include "minishell_test.h"

/* TODO More tests with file redirections when ready */

TestSuite(minishell_test_suite_cmd, .init=init_test, .fini=clean_test);

Test(minishell_test_suite_cmd, test_cmd_lst_1)
{
	char	*input = "ls -l";

	res = token_lst_build(ms, input);
	cr_assert_eq(res, 1);
	usual_flow(ms, input);
	cr_assert_str_eq(ms->cmd_lst->path, "/usr/bin/ls");
	cr_assert_str_eq(ms->cmd_lst->args[0], "ls");
	cr_assert_str_eq(ms->cmd_lst->args[1], "-l");
	cr_assert_null(ms->cmd_lst->args[2]);
	cr_assert_null(ms->cmd_lst->next);
}

Test(minishell_test_suite_cmd, test_cmd_lst_2)
{
	char	*input = "ls -l | wc -m -c";

	res = token_lst_build(ms, input);
	cr_assert_eq(res, 1);
	usual_flow(ms, input);
	paths = split_path_test(ms->env_lst);
	cmd_res = cmd_lst_build(ms, ms->token_lst);
	cr_assert_eq(cmd_res, 1);
	cr_assert_str_eq(ms->cmd_lst->path, "/usr/bin/ls");
	cr_assert_str_eq(ms->cmd_lst->args[0], "ls");
	cr_assert_str_eq(ms->cmd_lst->args[1], "-l");
	cr_assert_null(ms->cmd_lst->args[2]);
	cr_assert_str_eq(ms->cmd_lst->next->path, "/usr/bin/wc");
	cr_assert_str_eq(ms->cmd_lst->next->args[0], "wc");
	cr_assert_str_eq(ms->cmd_lst->next->args[1], "-m");
	cr_assert_str_eq(ms->cmd_lst->next->args[2], "-c");
	cr_assert_null(ms->cmd_lst->next->args[3]);
}
