#include "../include/minishell.h"

int	cmp(t_token_type a, t_token_type b)
{
	if (a == b)
		return (1);
	return (0);
}

void	token_joining(t_token **token_lst)
{
	t_token	*current;
	t_token	*n_token;
	char	*new_str;

	current = *token_lst;
	if (!current)
		return ;
	if (current && current->next && current->next->join)
	{
		n_token = current->next;
		while (n_token && n_token->join)
		{
			new_str = ft_strjoin(current->value, n_token->value);
			free(current->value);
			current->value = new_str;
			n_token = n_token->next;
		}
		token_joining(&n_token);
	}
	else
		token_joining(&current->next);
	token_lst_join_remove(token_lst);
}
