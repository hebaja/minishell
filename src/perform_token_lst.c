#include "../include/minishell.h"

void	expand(t_token *token)
{
	char	*USER = "hebatist";
	t_token	*next_token;

	if (token->type == DOLAR)
	{
		next_token = token->next;
		/* TODO search in internal environment variables here
		* when they're ready */
		if (ft_strcmp(next_token->value, "USER") == 0)
		{
			free(next_token->value);
			next_token->value = ft_strdup(USER);
		}
	}
}

int	cmp(t_token_type type_a, t_token_type type_b)
{
	if (type_a == type_b)
		return (1);
	return (0);
}

void token_lst_remove_if(t_token **token_lst, t_token_type type, int (*cmp)())
{
	t_token	*token;

	if (token_lst == NULL || *token_lst == NULL)
		return ;
	token = *token_lst;
	if (cmp(token->type, type))
	{
		*token_lst = token->next;
		token_clear(token);
		token_lst_remove_if(token_lst, type, cmp);
	}
	else
	{
		token = *token_lst;
		token_lst_remove_if(&token->next, type, cmp);
	}
}

void	variable_expansion(t_token **token_lst)
{
	token_lst_iterate(*token_lst, expand);
	token_lst_remove_if(token_lst, DOLAR, cmp);
}

int				token_lst_perform(t_token **token_lst)
{
	variable_expansion(token_lst);
	print_tokens(*token_lst);
	return (1);
}
