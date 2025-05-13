#include "minishell_test.h"

Test(minishell_test_suite_var, test_var_no_expansion_quote_1)
{
	char	*input = "\'$USER\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "$USER");
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_2)
{
	char	*input = "\'hello$USERhello\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello$USERhello");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hello$USERhello");
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_1)
{
	char	*input = "hello\'$USER\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\'$USER\'");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hello\'$USER\'");
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_2)
{
	char	*input = "hello\'hi $USER hello\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\'hi $USER hello\'");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hello\'hi $USER hello\'");
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_3)
{
	char	*input = "\'hello\'hello";

	values = populate_values(2, "hello", "hello");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_4)
{
	char	*input = "\'hello\'$USER";

	values = populate_values(2, "hello", "$USER");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_5)
{
	char	*input = "\'$USER\'$USER";

	values = populate_values(2, "$USER", "$USER");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote)
{
	char	*input = "\"$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hebatist");
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_1)
{
	char	*input = "\"$USER hello\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER hello");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hebatist hello");
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_2)
{
	char	*input = "\"hello $USER hello\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello $USER hello");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hello hebatist hello");
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_3)
{
	char	*input = "\"hello $USER hello\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello $USER hello");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hello hebatist hello");
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_4)
{
	char	*input = "\"hello $USER hello $USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello $USER hello $USER");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hello hebatist hello hebatist");
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_5)
{
	char	*input = "\"hello$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello$USER");
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hellohebatist");
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_1)
{
	char	*input = "echo \"$USER\"";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_2)
{
	char	*input = "echo \" $USER\"";

	values = populate_values(2, "echo", " $USER");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_3)
{
	char	*input = "echo \"hello $USER hello $USER\"";

	values = populate_values(2, "echo", "hello $USER hello $USER");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_4)
{
	char	*input = "echo\"$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "echo\"$USER\"");
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "echo\"hebatist\"");
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_5)
{
	char	*input = "echo\"hi $USER hello\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "echo\"hi $USER hello\"");
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "echo\"hi hebatist hello\"");
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_6)
{
	char	*input = "\"hello\"hello";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values = split_token_lst(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_7)
{
	char	*input = "\"$USER\"$USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values = split_token_lst(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_8)
{
	char	*input = "\"hello $USER hello\"$USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values = split_token_lst(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mult)
{
	char	*input = "\"hello\"\"hello\"";

	values = populate_values(2, "hello", "hello");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mult_raw)
{
	char	*input = "\"hello\"$USER\"hello\"";

	values = populate_values(3, "hello", "$USER", "hello");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_go_crazy)
{
	char	*input = "hello $USER \'$USER\'>\"$USER\"<< \'nice$USER\' | \"hello $USER $USER\" hello \'$USER\'\"$USER\"";

	values = populate_values(12, "hello", "$USER", "$USER", ">", "$USER", "<<", "nice$USER", "|", "hello $USER $USER", "hello", "$USER", "$USER");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}
