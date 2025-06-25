#include "minishell_test.h"
#include <unistd.h>

TestSuite(minishell_test_suite_join, .init=init_test, .fini=clean_test);

Test(minishell_test_suite_join, test_single_quote_token_join_1)
{
	char	*input = "\'hello\'hello";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "hellohello");
	cr_assert_eq(ms->token_lst->type, SINGLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_2)
{
	char	*input = "\'hello\'$USER";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	out_value = ft_strjoin("hello", get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_eq(ms->token_lst->type, SINGLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_3)
{
	char	*input = "\'$USER\'\'$USER\'";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "$USER$USER");
	cr_assert_eq(ms->token_lst->type, SINGLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_4)
{
	char	*input = "$USER\'$USER\'";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	out_value = ft_strjoin(get_var_value(ms->env_lst, "USER"), "$USER");
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_eq(ms->token_lst->type, VAR);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_1)
{
	char	*input = "\"hello\"hello";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "hellohello");
	cr_assert_eq(ms->token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_2)
{
	char	*input = "\"hello\"$USER";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	out_value = ft_strjoin("hello", get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_eq(ms->token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_3)
{
	char	*input = "\"$USER\"\"$USER\"";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	out_value = ft_strjoin(get_var_value(ms->env_lst, "USER"), get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_eq(ms->token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_4)
{
	char	*input = "$USER\"$USER\"";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	out_value = ft_strjoin(get_var_value(ms->env_lst, "USER"), get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_eq(ms->token_lst->type, VAR);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_mix_token_join_1)
{
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\"";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	out_value = multi_str_join(3, "hellohihey", get_var_value(ms->env_lst, "USER"), get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_eq(ms->token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_join, test_mix_token_join_2)
{
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\" hi\"hi\"$USER\'$USER\'";

	ms->input = input;
	res = token_lst_build(ms);
	values = populate_values(2, multi_str_join(3, "hellohihey", get_var_value(ms->env_lst, "USER"), get_var_value(ms->env_lst, "USER")),
		multi_str_join(3, "hihi", get_var_value(ms->env_lst, "USER"), "$USER")); 
	cr_assert_eq(res, 1);
	usual_flow(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_join, test_mix_token_join_3)
{
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\">hi\"hi\"$USER\'$USER\'";

	ms->input = input;
	res = token_lst_build(ms);
	values = populate_values(3, multi_str_join(3, "hellohihey", get_var_value(ms->env_lst, "USER"), get_var_value(ms->env_lst, "USER")),
		">", multi_str_join(3, "hihi", get_var_value(ms->env_lst, "USER"), "$USER")); 
	cr_assert_eq(res, 1);
	usual_flow(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	test_lst(ms->token_lst, values, types);
	unlink("hihifocus$USER");
}
