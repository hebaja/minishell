#ifndef MINISHELL_TEST_H
# define MINISHELL_TEST_H

# include "criterion-2.4.2/include/criterion/assert.h"
# include "criterion-2.4.2/include/criterion/criterion.h"
# include "criterion-2.4.2/include/criterion/redirect.h"
# include "../include/minishell.h"

void	redirect_all_stdout(void);
char    *fetch_token_type(t_token_type type);
char	**fetch_tokens_type_list(t_token *token_lst);
void	unquoted_value_test(t_token *token_lst, char *value, char quote);
void	test_token_lst(t_token *token_lst, char *value, char *type);

#endif
