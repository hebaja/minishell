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

Test(minishel_test_suite, build_simple_token_word)
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
