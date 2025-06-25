#include "minishell_test.h"

TestSuite(minishell_test_suite_basic, .init=init_test, .fini = clean_test);

Test(minishell_test_suite_basic, token_lst_one_size)
{
	char	*input = "command";

	ms->input = input;
	res = token_lst_build(ms);
	size = token_lst_size(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(size, 1);
}

Test(minishell_test_suite_basic, token_lst_n_size)
{
	char	*input = "command > file.txt << command";

	ms->input = input;
	res = token_lst_build(ms);
	size = token_lst_size(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(size, 5);
}

Test(minishell_test_suite_basic, build_token_lst_word)
{
	char	*input = "Hello";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(fetch_token_type(ms->token_lst->type), "WORD");
	cr_assert_str_eq(ms->token_lst->value, "Hello");
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_basic, build_token_lst_word_and_one_element)
{
	char		*input = "command >";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_and_n_elements)
{
	char		*input = "command > file.txt << command";

	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_with_one_flag)
{
	char	*input = "command -e";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_with_raw_flag)
{
	char	*input = "command -";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_with_n_flag)
{
	char	*input = "command -e -i --help";
	
	ms->input = input;
	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_basic_stderr, build_token_lst_null, .init=init_test_redirect_stderr)
{
	char	*input = "msg";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	ms->token_lst->value = NULL;
	cr_assert_null(ms->token_lst->value);
	conclude_parser(ms);
}
