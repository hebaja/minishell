#include "minishell_test.h"

TestSuite(minishell_test_extra_meta_test_alloc, .init=init_test_alloc_mem, .fini=clean_test);

Test(minishell_test_extra_meta_test_alloc, build_token_lst_test_dolar_var)
{
	char	*input = "echo $USER";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	values = populate_values(2, "echo", "$USER");
	cr_assert_eq(res, 1);
	cr_assert_eq(ms->token_lst->next->type, VAR);
	test_lst(ms->token_lst, values, types);
}
 
Test(minishell_test_extra_meta_test_alloc, build_token_lst_dolar_char)
{
	char	*input = "echo $ USER";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	values = populate_values(3, "echo", "$", "USER");
	cr_assert_eq(res, 1);
	cr_assert_neq(ms->token_lst->next->type, VAR);
	test_lst(ms->token_lst, values, types);
}

/*
Test(minishell_test_extra_meta_test, build_token_lst_wildcard_only)
{
	char	*input = "*";

	values = ft_split(input, ' ');
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(ms->token_lst->type, WILDCARD_SOLO);
	test_lst(ms->token_lst, values, types);
}
*/

Test(minishell_test_extra_meta_test_alloc, build_token_lst_wildcard_default)
{
	char	*input = "list *c";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	values = populate_values(3, "list", "*", "c");
	cr_assert_eq(res, 1);
	cr_assert_eq(ms->token_lst->next->type, WILDCARD_JOIN);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_extra_meta_test_alloc, build_token_lst_wildcard_solo)
{
	char	*input = "list * c";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	values = populate_values(3, "list", "*", "c");
	cr_assert_eq(res, 1);
	cr_assert_eq(ms->token_lst->next->type, WILDCARD_SOLO);
	test_lst(ms->token_lst, values, types);
}

Test(minishell_test_extra_meta_test_alloc, build_token_lst_wildcard_solo_end)
{
	char	*input = "list *";

	ms->input = input;
	res = token_lst_build(ms);
	types = fetch_tokens_type_list(ms->token_lst);
	values = populate_values(2, "list", "*");
	cr_assert_eq(res, 1);
	cr_assert_eq(ms->token_lst->next->type, WILDCARD_SOLO);
	test_lst(ms->token_lst, values, types);
}
