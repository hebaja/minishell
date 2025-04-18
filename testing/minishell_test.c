#include "minishell_test.h"

Test(minishell_test_suite, token_lst_one_size)
{
	int		res;
	char	*input = "command";
	size_t	size;
	t_token	*token_lst = NULL;

	res = token_lst_build(&token_lst, input);
	size = token_lst_size(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(size, 1);
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, token_lst_n_size)
{
	int		res;
	char	*input = "command > file.txt << command";
	size_t	size;
	t_token	*token_lst = NULL;

	res = token_lst_build(&token_lst, input);
	size = token_lst_size(token_lst);
	cr_assert_eq(res, 1);
	cr_assert_eq(size, 5);
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_word)
{
	int		res;
	t_token	*tokens_head;
	char	*input = "Hello";

	tokens_head = NULL;	
	res = token_lst_build(&tokens_head, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(fetch_token_type(tokens_head->type), "WORD");
	cr_assert_str_eq(tokens_head->value, "Hello");
	token_lst_clear(&tokens_head);
}

Test(minishell_test_suite, build_token_lst_word_and_one_element)
{
	t_token		*token_lst;
	int			i;
	int			res;
	char		*input = "command >";
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

Test(minishell_test_suite, build_token_lst_word_and_n_elements)
{
	t_token		*token_lst;
	int			res;
	int			i;
	char		*input = "command > file.txt << command";
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

Test(minishell_test_suite, build_token_lst_word_with_one_flag)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "command -e";
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

Test(minishell_test_suite, build_token_lst_word_with_raw_flag)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "command -";
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

Test(minishell_test_suite, build_token_lst_word_with_n_flag)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "command -e -i --help";
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
