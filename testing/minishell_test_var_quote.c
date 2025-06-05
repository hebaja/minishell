#include "minishell_test.h"

Test(minishell_test_suite_var, test_var_no_expansion_quote_1)
{
	char	*input = "\'$USER\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER");
	quotes_var_expansion(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "$USER");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_2)
{
	char	*input = "\'hello$USERhello\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello$USERhello");
	quotes_var_expansion(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hello$USERhello");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_1)
{
	char	*input = "hello\'$USER\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\'$USER\'");
	quotes_var_expansion(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hello\'$USER\'");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_2)
{
	char	*input = "hello\'hi $USER hello\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello\'hi $USER hello\'");
	quotes_var_expansion(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hello\'hi $USER hello\'");
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_3)
{
	char	*input = "\'hello\'hello";

	env_lst = build_envp();
	values = populate_values(2, "hello", "hello");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_4)
{
	char	*input = "\'hello\'$USER";

	env_lst = build_envp();
	values = populate_values(2, "hello", "$USER");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_no_expansion_quote_and_raw_5)
{
	char	*input = "\'$USER\'$USER";

	env_lst = build_envp();
	values = populate_values(2, "$USER", "$USER");
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote)
{
	char	*input = "\"$USER\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER");
	quotes_var_expansion(&token_lst, env_lst);
	out_value = get_var_value(env_lst, "USER");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_1)
{
	char	*input = "\"$USER hello\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER hello");
	quotes_var_expansion(&token_lst, env_lst);
	out_value = ft_strjoin(get_var_value(env_lst, "USER"), " hello");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_2)
{
	char	*input = "\"hello $USER hello\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello $USER hello");
	quotes_var_expansion(&token_lst, env_lst);
	out_value = multi_str_join(3, "hello ", get_var_value(env_lst, "USER"), " hello");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_3)
{
	char	*input = "\"hello $USER hello\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello $USER hello");
	quotes_var_expansion(&token_lst, env_lst);
	out_value = multi_str_join(3, "hello ", get_var_value(env_lst, "USER"), " hello");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_4)
{
	char	*input = "\"hello $USER hello $TERM\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello $USER hello $TERM");
	quotes_var_expansion(&token_lst, env_lst);
	out_value = multi_str_join(4, "hello ", get_var_value(env_lst, "USER"), " hello ", get_var_value(env_lst, "TERM"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mix_5)
{
	char	*input = "\"hello$USER\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "hello$USER");
	quotes_var_expansion(&token_lst, env_lst);
	out_value = ft_strjoin("hello", get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_1)
{
	char	*input = "echo \"$USER\"";

	env_lst = build_envp();
	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_2)
{
	char	*input = "echo \" $USER\"";

	env_lst = build_envp();
	values = populate_values(2, "echo", " $USER");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_3)
{
	char	*input = "echo \"hello $USER hello $USER\"";

	env_lst = build_envp();
	values = populate_values(2, "echo", "hello $USER hello $USER");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_4)
{
	char	*input = "echo\"$USER\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "echo\"$USER\"");
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	out_value = multi_str_join(4, "echo", "\"", get_var_value(env_lst, "USER"), "\"");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_5)
{
	char	*input = "echo\"hi $USER hello\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "echo\"hi $USER hello\"");
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	out_value = multi_str_join(3, "echo\"hi ", get_var_value(env_lst, "USER"), " hello\"");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_6)
{
	char	*input = "\"hello\"hello";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values = split_token_lst(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_7)
{
	char	*input = "\"$USER\"$USER";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values = split_token_lst(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_and_raw_8)
{
	char	*input = "\"hello $USER hello\"$USER";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values = split_token_lst(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mult)
{
	char	*input = "\"hello\"\"hello\"";

	env_lst = build_envp();
	values = populate_values(2, "hello", "hello");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_mult_raw)
{
	char	*input = "\"hello\"$USER\"hello\"";

	env_lst = build_envp();
	values = populate_values(3, "hello", "$USER", "hello");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_quote_go_crazy)
{
	char	*input = "hello $USER \'$USER\'>\"$USER\"<< \'nice$USER\' | \"hello $USER $USER\" hello \'$USER\'\"$USER\"";

	env_lst = build_envp();
	values = populate_values(12, "hello", "$USER", "$USER", ">", "$USER", "<<", "nice$USER", "|", "hello $USER $USER", "hello", "$USER", "$USER");		
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	quotes_var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}
