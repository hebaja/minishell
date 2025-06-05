#include "minishell_test.h"

/* TODO More tests with file redirections when ready */

TestSuite(minishell_test_suite_cmd, .fini=clean_test);

Test(minishell_test_suite_cmd, test_cmd_lst_1)
{
	char	*input = "ls -l";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	paths = split_path(env_lst);
	cmd_res = cmd_lst_build(&cmd_lst, token_lst, paths);
	cr_assert_eq(cmd_res, 1);
	cr_assert_str_eq(cmd_lst->path, "/usr/bin/ls");
	cr_assert_str_eq(cmd_lst->args[0], "ls");
	cr_assert_str_eq(cmd_lst->args[1], "-l");
	cr_assert_null(cmd_lst->args[2]);
	cr_assert_null(cmd_lst->next);
}

Test(minishell_test_suite_cmd, test_cmd_lst_2)
{
	char	*input = "ls -l | wc -m -c";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	paths = split_path(env_lst);
	cmd_res = cmd_lst_build(&cmd_lst, token_lst, paths);
	cr_assert_eq(cmd_res, 1);
	cr_assert_str_eq(cmd_lst->path, "/usr/bin/ls");
	cr_assert_str_eq(cmd_lst->args[0], "ls");
	cr_assert_str_eq(cmd_lst->args[1], "-l");
	cr_assert_null(cmd_lst->args[2]);
	cr_assert_str_eq(cmd_lst->next->path, "/usr/bin/wc");
	cr_assert_str_eq(cmd_lst->next->args[0], "wc");
	cr_assert_str_eq(cmd_lst->next->args[1], "-m");
	cr_assert_str_eq(cmd_lst->next->args[2], "-c");
	cr_assert_null(cmd_lst->next->args[3]);
}
