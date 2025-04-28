#include "../include/minishell.h"

void	token_clear(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
	token = NULL;
}

void	token_lst_clear(t_token **token_lst)
{
	if (token_lst != NULL)
		token_lst_iterate(*token_lst, token_clear);
	*token_lst = NULL;
}
