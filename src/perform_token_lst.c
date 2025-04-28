#include "../include/minishell.h"

int				token_lst_perform(t_token **token_lst)
{
	print_tokens(*token_lst);
	return (1);
}
