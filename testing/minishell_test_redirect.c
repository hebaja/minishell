#include "minishell_test.h"

Test(minishell_test_suite_redirect, test_redirect_out)
{
	char	*input = "echo helo > out";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, 1);
}

Test(minishell_test_suite_redirect, test_append)
{
	char	*input = "echo helo >> out";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, 1);
}

Test(minishell_test_suite_redirect, test_redirect_in)
{
	char	*input = "grep Jolyne < file";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, 1);
}

Test(minishell_test_suite_redirect, test_heredoc)
{
	char	*input = "grep Jolyne << EOF > out";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, 2);
}

Test(minishell_test_suite_redirect, test_redirect_out_error)
{
	char	*input = "echo helo >";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, -1);
}

Test(minishell_test_suite_redirect, test_append_error)
{
	char	*input = "echo helo >>";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, -1);
}

Test(minishell_test_suite_redirect, test_redirect_in_error)
{
	char	*input = "grep Jolyne <";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, -1);
}

Test(minishell_test_suite_redirect, test_heredoc_error)
{
	char	*input = "grep Jolyne << EOF >";
	int		red_res;

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	red_res = check_redirect(token_lst);
	cr_assert_eq(red_res, -1);
}
