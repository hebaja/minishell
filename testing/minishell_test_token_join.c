#include "minishell_test.h"

Test(minishell_test_suite_join, test_single_quote_token_join_1)
{
	char	*input = "\'hello\'hello";

	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
	cr_assert_eq(token_lst->type, SINGLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_2)
{
	char	*input = "\'hello\'$USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hellohebatist");
	cr_assert_eq(token_lst->type, SINGLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_3)
{
	char	*input = "\'$USER\'\'$USER\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "$USER$USER");
	cr_assert_eq(token_lst->type, SINGLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_4)
{
	char	*input = "$USER\'$USER\'";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hebatist$USER");
	cr_assert_eq(token_lst->type, VAR);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_1)
{
	char	*input = "\"hello\"hello";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_2)
{
	char	*input = "\"hello\"$USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hellohebatist");
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_3)
{
	char	*input = "\"$USER\"\"$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hebatisthebatist");
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_4)
{
	char	*input = "$USER\"$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hebatisthebatist");
	cr_assert_eq(token_lst->type, VAR);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_mix_token_join_1)
{
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\"";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	cr_assert_str_eq(token_lst->value, "hellohiheyhebatisthebatist");
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_mix_token_join_2)
{
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\" hi\"hi\"$USER\'$USER\'";

	res = token_lst_build(&token_lst, input);
	values = populate_values(2, "hellohiheyhebatisthebatist", "hihihebatist$USER");
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	types = fetch_tokens_type_list(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_join, test_mix_token_join_3)
{
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\">hi\"hi\"$USER\'$USER\'";

	res = token_lst_build(&token_lst, input);
	values = populate_values(3, "hellohiheyhebatisthebatist", ">", "hihihebatist$USER");
	cr_assert_eq(res, 1);
	usual_flow(&token_lst);
	types = fetch_tokens_type_list(token_lst);
	test_lst(token_lst, values, types);
}
