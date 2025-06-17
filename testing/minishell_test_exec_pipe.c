#include "minishell_test.h"

TestSuite(minishell_test_exec_pipe, .init=init_test_redirect_stdout, .fini=clean_test);

Test(minishell_test_exec_pipe, exec_test_1)
{
	char	*input = "whoami";
	char	*out_res;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	exec_cmd(ms);
	out_res = ft_strjoin(getenv("USER"), "\n");
	cr_assert_stdout_eq_str(out_res);
}

Test(minishell_test_exec_pipe, pipe_builtin_test_1)
{
	char	*input = "env | grep USER";
	char	*out_res;

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	exec_cmd(ms);
	out_res = multi_str_join(3, "USER=", getenv("USER"), "\n");
	cr_assert_stdout_eq_str(out_res);
}

Test(minishell_test_exec_pipe, pipe_builtin_test_2)
{
	char	*input = "env | grep USER | wc -l";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	exec_cmd(ms);
	cr_assert_stdout_eq_str("1\n");
}
/*
Test(minishell_test_exec_pipe, exec_pipe_1)
{
	char	*input = "file --help | grep raw | awk '{print $2}'";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	exec_cmd(ms);
	cr_assert_stdout_eq_str("--raw\n");
}
*/
Test(minishell_test_exec_pipe_error, exec_not_found, .init=init_test_redirect_stderr, .fini=clean_test)
{
	char	*input = "jkd";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	exec_cmd(ms);
	cr_assert_stderr_eq_str("jkd: command not found\n");
}
