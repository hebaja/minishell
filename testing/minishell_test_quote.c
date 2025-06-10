#include "minishell_test.h"

TestSuite(minishell_test_suite_quote, .init=init_test_redirect_stderr, .fini=clean_test);

Test(minishell_test_suite_quote, build_token_lst_double_quote_1)
{
	char	*input = "echo \"message\"";
	
	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_single_quote_1)
{
	char	*input = "echo \'message\'";

	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_double_quote_2)
{
	char	*input = "echo \"message\" >> command";

	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_single_quote_2)
{
	char	*input = "echo \'message\' > command";
	
	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_double_quote_mixed)
{
	char	*input = "hello\"message\"";

	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_single_quote_mixed)
{
	char	*input = "hello\'message\'";
	
	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_single_quote_empty_1)
{
	char	*input = "\'\'";
	
	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_single_quote_empty_2)
{
	char	*input = "\'\'\'\'";
	
	values = populate_values(2, "", "");
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_double_quote_empty_1)
{
	char	*input = "\"\"";
	
	values = ft_split(input, ' ');
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_double_quote_empty_2)
{
	char	*input = "\"\"\"\"";
	
	values = populate_values(2, "", "");
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_quote, build_token_lst_single_double_empty)
{
	char	*input = "\'\'\"\"";
	
	values = populate_values(2, "", "");
	res = token_lst_build(ms, input);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}





Test(minishell_test_suite_quote, build_token_lst_single_quote_unclosed_1)
{
	char	*input = "\'hello";
	
	res = token_lst_build(ms, input);
	cr_assert_eq(res, 0);
}

Test(minishell_test_suite_quote, build_token_lst_single_quote_unclosed_2)
{
	char	*input = "\'";
	
	res = token_lst_build(ms, input);
	cr_assert_eq(res, 0);
}

Test(minishell_test_suite_quote, build_token_lst_double_quote_unclosed_1)
{
	char	*input = "\"hello";
	
	res = token_lst_build(ms, input);
	cr_assert_eq(res, 0);
}

Test(minishell_test_suite_quote, build_token_lst_double_quote_unclosed_2)
{
	char	*input = "\"";
	
	res = token_lst_build(ms, input);
	cr_assert_eq(res, 0);
}
