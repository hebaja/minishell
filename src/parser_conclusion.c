#include "../include/minishell.h"

int	check_token_integrity(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->value == NULL)
			return (0);
		token_lst = token_lst->next;
	}
	return (1);
}

void	builtin_recheck(t_token *token)
{
	if (token->value)
		define_type_builtin(token->value, &token->type);
}

void	conclude_parser(t_token *token_lst)
{
	token_lst_iterate(token_lst, builtin_recheck);
	check_token_integrity(token_lst);
}
