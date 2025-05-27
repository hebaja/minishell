#include "minishell_test.h"

TestSuite(minishell_test_suite_redirect, .init = redirect_stdout_err);

Test(minishell_test_suite_redirect, test_redirect_out)
{
	char	*input = "echo helo > out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 1);
}

Test(minishell_test_suite_redirect, test_append)
{
	char	*input = "echo helo >> out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 1);
}

Test(minishell_test_suite_redirect, test_redirect_in)
{
	char	*input = "grep Jolyne < file";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 1);
}

Test(minishell_test_suite_redirect, test_heredoc)
{
	char	*input = "grep Jolyne << EOF > out";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(red_res, 2);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_1)
{
	char	*input = "echo helo >";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_2)
{
	char	*input = "echo hello > > out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_3)
{
	char	*input = "echo hello >| out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_1)
{
	char	*input = "echo helo >>";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_2)
{
	char	*input = "echo helo >> <";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_3)
{
	char	*input = "echo helo >>| out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_1)
{
	char	*input = "grep Jolyne <";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_2)
{
	char	*input = "grep Jolyne < >> out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_3)
{
	char	*input = "grep Jolyne <| out";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_1)
{
	char	*input = "grep Jolyne << EOF >";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_2)
{
	char	*input = "grep Jolyne <<";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_3)
{
	char	*input = "grep Jolyne <<|";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_4)
{
	char	*input = "grep Jolyne << >";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}
