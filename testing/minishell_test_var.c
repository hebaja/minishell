#include "minishell_test.h"

Test(minishell_test_suite_var, test_var_expansion)
{
	char	*input = "$USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER");
	var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "hebatist");
}

Test(minishell_test_suite_var, test_var_expansion_join)
{
	char	*input = "sh$USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "sh$USER");
	var_expansion(&token_lst);
	cr_assert_str_eq(token_lst->value, "shhebatist");
}

Test(minishell_test_suite_var, test_var_expansion_mix)
{
	char	*input = "echo $USER hello";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_mix_mult)
{
	char	*input = "echo $USER hello $USER";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_mix_no_space)
{
	char	*input = "echo>>$USER";

	values = populate_values(3, "echo", ">>", "$USER");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}
