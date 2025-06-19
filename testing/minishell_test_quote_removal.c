#include "minishell_test.h"

TestSuite(minishell_test_suite_quote_removal, .init=init_test, .fini=clean_test);

Test(minishell_test_suite_quote_removal, test_single_quote_removal_1)
{
	char	*input = "hello\'hello\'";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "hello'hello\'");
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "hellohello");
}

Test(minishell_test_suite_quote_removal, test_single_quote_removal_2)
{
	char	*input = "hello\'$USER\'";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "hello'$USER\'");
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "hello$USER");
}

Test(minishell_test_suite_quote_removal, test_double_quote_removal_1)
{
	char	*input = "hello\"hello\"";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "hello\"hello\"");
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "hellohello");
}

Test(minishell_test_suite_quote_removal, test_double_quote_removal_2)
{
	char	*input = "hello\"$USER\"";
	char	*str;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "hello\"$USER\"");
	usual_flow(ms);
	str = ft_strjoin("hello", get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, str);
}
