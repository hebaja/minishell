#include "minishell_test.h"

TestSuite(minishell_test_suite_redirect, .init=init_test_redirect_stderr, .fini=clean_test);

Test(minishell_test_suite_redirect, test_redirect_out)
{
	char	*input = "echo helo > out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 1);
}

Test(minishell_test_suite_redirect, test_append)
{
	char	*input = "echo helo >> out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 1);
}

Test(minishell_test_suite_redirect, test_redirect_in)
{
	char	*input = "grep Jolyne < file";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 1);
}

Test(minishell_test_suite_redirect, test_heredoc)
{
	char	*input = "grep Jolyne << EOF > out";
	int		red_res;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(red_res, 2);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_1)
{
	char	*input = "echo helo >";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);

}

Test(minishell_test_suite_redirect, test_redirect_out_error_2)
{
	char	*input = "echo hello > > out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_3)
{
	char	*input = "echo hello >| out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_1)
{
	char	*input = "echo helo >>";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_2)
{
	char	*input = "echo helo >> <";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_3)
{
	char	*input = "echo helo >>| out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_1)
{
	char	*input = "grep Jolyne <";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_2)
{
	char	*input = "grep Jolyne < >> out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_3)
{
	char	*input = "grep Jolyne <| out";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_1)
{
	char	*input = "grep Jolyne << EOF >";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_2)
{
	char	*input = "grep Jolyne <<";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_3)
{
	char	*input = "grep Jolyne <<|";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_4)
{
	char	*input = "grep Jolyne << >";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_eq(conclude_parser(ms->token_lst), 0);
}
