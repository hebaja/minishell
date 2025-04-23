#include "minishell_test.h"

void	setup_alloc_mem(void)
{
	values = malloc(sizeof(char *) * 4);
	types = malloc(sizeof(char *) * 4);
}

TestSuite(minishell_test_extra_meta_test_alloc, .init = setup_alloc_mem);

Test(minishell_test_extra_meta_test_alloc, build_token_lst_test_dolar_var)
{
	char	*input = "echo $USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values[0] = ft_strdup("echo");
	values[1] = ft_strdup("$");
	values[2] = ft_strdup("USER");
	values[3] = NULL;
	cr_assert_eq(res, 1);
	cr_assert_eq(token_lst->next->type, DOLAR);
	test_lst(token_lst, values, types);
}
 
Test(minishell_test_extra_meta_test_alloc, build_token_lst_dolar_char)
{
	char	*input = "echo $ USER";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values[0] = ft_strdup("echo");
	values[1] = ft_strdup("$");
	values[2] = ft_strdup("USER");
	values[3] = NULL;
	cr_assert_eq(res, 1);
	cr_assert_neq(token_lst->next->type, DOLAR);
	test_lst(token_lst, values, types);
}

Test(minishell_test_extra_meta_test, build_token_lst_wildcard_only)
{
	char	*input = "*";

	values = ft_split(input, ' ');
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(token_lst->type, WILDCARD_SOLO);
	test_lst(token_lst, values, types);
}

Test(minishell_test_extra_meta_test_alloc, build_token_lst_wildcard_default)
{
	char	*input = "list *c";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values[0] = ft_strdup("list");
	values[1] = ft_strdup("*");
	values[2] = ft_strdup("c");
	values[3] = NULL;
	cr_assert_eq(res, 1);
	cr_assert_eq(token_lst->next->type, WILDCARD_JOIN);
	test_lst(token_lst, values, types);
}

Test(minishell_test_extra_meta_test_alloc, build_token_lst_wildcard_solo)
{
	char	*input = "list * c";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values[0] = ft_strdup("list");
	values[1] = ft_strdup("*");
	values[2] = ft_strdup("c");
	values[3] = NULL;
	cr_assert_eq(res, 1);
	cr_assert_eq(token_lst->next->type, WILDCARD_SOLO);
	test_lst(token_lst, values, types);
}

Test(minishell_test_extra_meta_test_alloc, build_token_lst_wildcard_solo_end)
{
	char	*input = "list *";

	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	values[0] = ft_strdup("list");
	values[1] = ft_strdup("*");
	values[2] = NULL;
	cr_assert_eq(res, 1);
	cr_assert_eq(token_lst->next->type, WILDCARD_SOLO);
	test_lst(token_lst, values, types);
}
