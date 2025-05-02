#include "../include/minishell.h"

/* RAW ENV EXPANSION 
* check if return void or int
*/
char	*USER = "hebatist";

void	expand(t_token *token)
{
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

/* RAW ENV EXPANSION */

/* DOUBLE QUOTED ENV EXPANSION 
* check if return void or int 
*/

int	expand_in_quote(t_token *token_lst, int i)
{
	printf("%c\n", token_lst->value[i]);
	/* TODO Try remember how use ft_strtrim from libfr
	 * it might be useful here
	 */
	return (1);
}

int	there_is_dolar(t_token *token_lst)
{
	int	i;

	i = -1;
	while (token_lst->value[++i])
	{
		if (token_lst->value[i] == '$')
		{
			if (token_lst->value[i + 1] != ' ')
			{
				printf("var\n");
				expand_in_quote(token_lst, i);
			}
		}
	}
	return (0);
}

void	check(t_token *token_lst)
{
	if (token_lst->type == DOUBLE_QUOTED)
			there_is_dolar(token_lst);	
}

void	double_quote_var_expansion(t_token **token_lst)
{
	token_lst_iterate(*token_lst, check); 
}


/* DOUBLE QUOTED ENV EXPANSION */

void	var_expansion(t_token **token_lst)
{
	token_lst_iterate(*token_lst, expand);
	token_lst_remove_if(token_lst, DOLAR, cmp);
}

int				token_lst_perform(t_token **token_lst)
{
	var_expansion(token_lst);
	double_quote_var_expansion(token_lst);
	print_tokens(*token_lst);
	return (1);
}
