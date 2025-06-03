#include "minishell_test.h"

TestSuite(minishell_test_suite_redirect, .init = redirect_stderr);

Test(minishell_test_suite_redirect, test_redirect_out)
{
	t_env	*env_lst;
	char	*input = "echo helo > out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 1);
}

Test(minishell_test_suite_redirect, test_append)
{
	t_env	*env_lst;
	char	*input = "echo helo >> out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 1);
}

Test(minishell_test_suite_redirect, test_redirect_in)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne < file";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 1);
}

Test(minishell_test_suite_redirect, test_heredoc)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne << EOF > out";
	int		red_res;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(red_res, 2);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_1)
{
	t_env	*env_lst;
	char	*input = "echo helo >";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);

}

Test(minishell_test_suite_redirect, test_redirect_out_error_2)
{
	t_env	*env_lst;
	char	*input = "echo hello > > out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_out_error_3)
{
	t_env	*env_lst;
	char	*input = "echo hello >| out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_1)
{
	t_env	*env_lst;
	char	*input = "echo helo >>";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_2)
{
	t_env	*env_lst;
	char	*input = "echo helo >> <";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_append_error_3)
{
	t_env	*env_lst;
	char	*input = "echo helo >>| out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_1)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne <";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_2)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne < >> out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_redirect_in_error_3)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne <| out";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_1)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne << EOF >";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_2)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne <<";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_3)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne <<|";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}

Test(minishell_test_suite_redirect, test_heredoc_error_4)
{
	t_env	*env_lst;
	char	*input = "grep Jolyne << >";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_eq(conclude_parser(token_lst), 0);
}
