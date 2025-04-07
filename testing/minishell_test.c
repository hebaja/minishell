#include "criterion-2.4.2/include/criterion/assert.h"
#include "criterion-2.4.2/include/criterion/criterion.h"
#include "criterion-2.4.2/include/criterion/redirect.h"
#include "../include/minishell.h"

void redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

char    *fetch_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	return ("");
}

void	test_token_lst(t_token *token_lst, char *value, char *type)
{
	cr_assert_str_eq(token_lst->value, value);
	cr_assert_str_eq(fetch_token_type(token_lst->type), type);
}

char	**fetch_tokens_type_list(t_token *token_lst)
{
	char	**tokens_type_list;
	char	*type_str;
	size_t	size;
	int		i;

	tokens_type_list = (char **)malloc(sizeof(char *) * (token_lst_size(token_lst) + 1));
	i = 0;
	while (token_lst)
	{
		size = 0;
		type_str = fetch_token_type(token_lst->type);
		size = ft_strlen(type_str);
		tokens_type_list[i] = strdup(type_str);
		token_lst = token_lst->next;
		i++;
	}
	return (tokens_type_list);
}

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
