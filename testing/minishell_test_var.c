#include "minishell_test.h"

TestSuite(minishell_test_suite_var, .init=init_test, .fini=clean_test);

Test(minishell_test_suite_var, test_var_expansion)
{
	char	*input = "$USER";
	char	*var_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	var_value = get_var_value(ms->env_lst, "USER");
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "$USER");
	var_expansion(&ms->token_lst, ms->env_lst);
	cr_assert_str_eq(ms->token_lst->value, var_value);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_var, test_var_expansion_join)
{
	char	*input = "sh$USER";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(ms->token_lst->value, "sh$USER");
	var_expansion(&ms->token_lst, ms->env_lst);
	out_value = ft_strjoin("sh", get_var_value(ms->env_lst, "USER"));
	cr_assert_str_eq(ms->token_lst->value, out_value);
	cr_assert_null(ms->token_lst->next);
	free(out_value);
}

Test(minishell_test_suite_var, test_var_expansion_mix)
{
	char	*input = "echo $USER hello";
	char	*out_value;

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	values = populate_values(3, "echo", "$USER", "hello");
	test_lst(ms->token_lst, values, types);
	var_expansion(&ms->token_lst, ms->env_lst);
	clean_values(values);
	values = split_token_lst(ms->token_lst);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_mix_mult)
{
	char	*input = "echo $USER hello $USER";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	values = populate_values(4, "echo", "$USER", "hello", "$USER");
	test_lst(ms->token_lst, values, types);
	var_expansion(&ms->token_lst, ms->env_lst);
	clean_values(values);
	values = split_token_lst(ms->token_lst);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_mix_no_space)
{
	char	*input = "echo>>$USER";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	values = populate_values(3, "echo", ">>", "$USER");
	test_lst(ms->token_lst, values, types);
	var_expansion(&ms->token_lst, ms->env_lst);
	clean_values(values);
	values = split_token_lst(ms->token_lst);
	test_lst(ms->token_lst, values, types);
}
