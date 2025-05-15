#include "minishell_test.h"

Test(minishell_test_suite_join, test_token_join)
{
	char	*input = "\'hello\'hello";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	var_expansion(&token_lst);
	quotes_var_expansion(&token_lst);
	quote_removal(token_lst);
	token_joining(&token_lst);
	cr_assert_str_eq(token_lst->value, "\'hellohello\'");
}
