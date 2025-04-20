#include "minishell_test.h"

Test(minishell_test_suite, build_token_lst_test_dolar_var)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "echo $USER";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}
 
