#include "criterion-2.4.2/include/criterion/assert.h"
#include "criterion-2.4.2/include/criterion/criterion.h"
#include "criterion-2.4.2/include/criterion/redirect.h"
#include "../include/minishell.h"

#include <stdio.h>

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

Test(minishell_test_suite, token_lst_size)
{
	int		res;
	char	*input = "command";
	size_t	size;
	t_token	*token_lst = NULL;

	res = token_lst_build(&token_lst, input);
	size = token_lst_size(token_lst);

	ft_printf("%d\n", size);

	cr_assert_eq(res, 1);
	cr_assert_eq(size, 1);
}

// char	**fetch_tokens_type_list(t_token *token_lst)
// {
// 	char	**tokens_type_list;
// 	char	*type;
// 	size_t	size;

// 	while (token_lst)
// 	{
// 		type = fetch_token_type(token_lst->type);
// 		size = ft_strlen(type);
// 		tokens_type_list = (t_token **)
// 	}
// }

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
}

Test(minishell_test_suite, build_token_lst_word_and_one_element)
{
	int	res;
	t_token	*token_lst;
	char	*input = "command >";
	
	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	cr_assert_str_eq(token_lst->value, "command");
	cr_assert_str_eq(fetch_token_type(token_lst->type), "WORD");
	token_lst = token_lst->next;	
	cr_assert_str_eq(token_lst->value, ">");
	cr_assert_str_eq(fetch_token_type(token_lst->type), "REDIRECT_OUT");
}

void	test_token_lst(t_token *token_lst, char *value, char *type)
{
	cr_assert_str_eq(token_lst->value, value);
	cr_assert_str_eq(fetch_token_type(token_lst->type), type);
}

Test(minishell_test_suite, build_token_lst_word_and_n_elements)
{
	int	res;
	t_token	*token_lst;
	char	*input = "command > file.txt << command";
	char	**values = ft_split(input, ' ');
	
	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	test_token_lst(token_lst, values[0], "WORD");
	token_lst = token_lst->next;
	test_token_lst(token_lst, values[1], "REDIRECT_OUT");
	// cr_assert_str_eq(fetch_token_type(token_lst->type), "REDIRECT_OUT");
	// cr_assert_str_eq(token_lst->value, ">");
}
