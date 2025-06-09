#include "minishell_test.h"

TestSuite(minishell_test_suite_join, .fini=clean_test);

Test(minishell_test_suite_join, test_single_quote_token_join_1)
{
	t_env	*env_lst;
	char	*input = "\'hello\'hello";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
	cr_assert_eq(token_lst->type, SINGLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_2)
{
	t_env	*env_lst;
	char	*input = "\'hello\'$USER";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	out_value = ft_strjoin("hello", get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_eq(token_lst->type, SINGLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_3)
{
	t_env	*env_lst;
	char	*input = "\'$USER\'\'$USER\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "$USER$USER");
	cr_assert_eq(token_lst->type, SINGLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_single_quote_token_join_4)
{
	t_env	*env_lst;
	char	*input = "$USER\'$USER\'";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	out_value = ft_strjoin(get_var_value(env_lst, "USER"), "$USER");
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_eq(token_lst->type, VAR);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_1)
{
	t_env	*env_lst;
	char	*input = "\"hello\"hello";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "hellohello");
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_2)
{
	t_env	*env_lst;
	char	*input = "\"hello\"$USER";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	out_value = ft_strjoin("hello", get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_3)
{
	t_env	*env_lst;
	char	*input = "\"$USER\"\"$USER\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	out_value = ft_strjoin(get_var_value(env_lst, "USER"), get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_double_quote_token_join_4)
{
	t_env	*env_lst;
	char	*input = "$USER\"$USER\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	out_value = ft_strjoin(get_var_value(env_lst, "USER"), get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_eq(token_lst->type, VAR);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_mix_token_join_1)
{
	t_env	*env_lst;
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\"";
	char	*out_value;

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	out_value = multi_str_join(3, "hellohihey", get_var_value(env_lst, "USER"), get_var_value(env_lst, "USER"));
	cr_assert_str_eq(token_lst->value, out_value);
	cr_assert_eq(token_lst->type, DOUBLE_QUOTED);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_join, test_mix_token_join_2)
{
	t_env	*env_lst;
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\" hi\"hi\"$USER\'$USER\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	values = populate_values(2, multi_str_join(3, "hellohihey", get_var_value(env_lst, "USER"), get_var_value(env_lst, "USER")),
		multi_str_join(3, "hihi", get_var_value(env_lst, "USER"), "$USER")); 
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	types = fetch_tokens_type_list(token_lst);
	test_lst(token_lst, values, types);
}

Test(minishell_test_suite_join, test_mix_token_join_3)
{
	t_env	*env_lst;
	char	*input = "\"hello\"hi\'hey\'$USER\"$USER\">hi\"hi\"$USER\'$USER\'";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	values = populate_values(3, multi_str_join(3, "hellohihey", get_var_value(env_lst, "USER"), get_var_value(env_lst, "USER")),
		">", multi_str_join(3, "hihi", get_var_value(env_lst, "USER"), "$USER")); 
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	types = fetch_tokens_type_list(token_lst);
	test_lst(token_lst, values, types);
}
