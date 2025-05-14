#include "minishell_test.h"

Test(minishell_test_suite_quote_removal, test_single_quote_removal_1)
{
	char	*input = "hello\'hello\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello'hello\'");
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	quote_removal(token_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
}

Test(minishell_test_suite_quote_removal, test_single_quote_removal_2)
{
	char	*input = "hello\'$USER\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello'$USER\'");
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	quote_removal(token_lst);
	cr_assert_str_eq(token_lst->value, "hello$USER");
}

Test(minishell_test_suite_quote_removal, test_double_quote_removal_1)
{
	char	*input = "hello\"hello\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\"hello\"");
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	quote_removal(token_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
}

Test(minishell_test_suite_quote_removal, test_double_quote_removal_2)
{
	char	*input = "hello\"$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\"hebatist\"");
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	quote_removal(token_lst);
	cr_assert_str_eq(token_lst->value, "hellohebatist");
}
