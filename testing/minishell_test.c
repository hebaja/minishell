#include "minishell_test.h"

Test(minishell_test_suite_basic, token_lst_one_size)
{
	char	*input = "command";

	res = token_lst_build(&token_lst, input);
	size = token_lst_size(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(size, 1);
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite_basic, token_lst_n_size)
{
	char	*input = "command > file.txt << command";

	res = token_lst_build(&token_lst, input);
	size = token_lst_size(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(size, 5);
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite_basic, build_token_lst_word)
{
	char	*input = "Hello";

	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(fetch_token_type(token_lst->type), "WORD");
	cr_assert_str_eq(token_lst->value, "Hello");
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite_basic, build_token_lst_word_and_one_element)
{
	char		*input = "command >";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_and_n_elements)
{
	char		*input = "command > file.txt << command";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_with_one_flag)
{
	char	*input = "command -e";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite_basic, build_token_lst_word_with_raw_flag)
{
	char	*input = "command -";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_basic, build_token_lst_word_with_n_flag)
{
	char	*input = "command -e -i --help";
	
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
}
