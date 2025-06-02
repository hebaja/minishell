#include "minishell_test.h"

Test(minishell_test_suite_var, test_var_expansion)
{
	t_env	*env_lst;
	char	*input = "$USER";
	char	*var_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	var_value = get_var_value(env_lst, "USER");
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "$USER");
	var_expansion(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, var_value);
	cr_assert_null(token_lst->next);
	free(var_value);
}

Test(minishell_test_suite_var, test_var_expansion_join)
{
	t_env	*env_lst;
	char	*input = "sh$USER";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "sh$USER");
	var_expansion(&token_lst, env_lst);
	out_value = ft_strjoin("sh", get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_null(token_lst->next);
	free(out_value);
}

Test(minishell_test_suite_var, test_var_expansion_mix)
{
	t_env	*env_lst;
	char	*input = "echo $USER hello";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	values = populate_values(3, "echo", "$USER", "hello");
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_mix_mult)
{
	t_env	*env_lst;
	char	*input = "echo $USER hello $USER";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	values = populate_values(4, "echo", "$USER", "hello", "$USER");
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_var, test_var_expansion_mix_no_space)
{
	t_env	*env_lst;
	char	*input = "echo>>$USER";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	values = populate_values(3, "echo", ">>", "$USER");
	test_lst(token_lst, values, types);
	var_expansion(&token_lst, env_lst);
	clean_values(values);
	values = split_token_lst(token_lst);
	test_lst(token_lst, values, types);
}
