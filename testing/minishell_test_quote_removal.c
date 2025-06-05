#include "minishell_test.h"

TestSuite(minishell_test_suite_quote_removal, .fini=clean_test);

Test(minishell_test_suite_quote_removal, test_single_quote_removal_1)
{
	char	*input = "hello\'hello\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello'hello\'");
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
}

Test(minishell_test_suite_quote_removal, test_single_quote_removal_2)
{
	char	*input = "hello\'$USER\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello'$USER\'");
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hello$USER");
}

Test(minishell_test_suite_quote_removal, test_double_quote_removal_1)
{
	char	*input = "hello\"hello\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\"hello\"");
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
}

Test(minishell_test_suite_quote_removal, test_double_quote_removal_2)
{
	char	*input = "hello\"$USER\"";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\"hebatist\"");
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hellohebatist");
}
