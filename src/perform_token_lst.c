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
		if (ft_strncmp(next_token->value, "USER", ft_strlen("USER")) == 0)
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

int	expand_in_quote(t_token *token_lst, int dolar_pos)
{
	int		env_name_len;
	int		old_value_len;
	int		new_value_len;
	int		var_value_len;
	int		var_key_len;
	char	*env_name;
	char	*new_value;
	int		i;
	int		j;


	i = -1;

	env_name_len = 0;
	while (token_lst->value[++i] != '$');
	while (ft_isalnum(token_lst->value[++i]))
		env_name_len++;
	env_name = ft_substr(token_lst->value, dolar_pos + 1, env_name_len);

	/* TODO this is where we must look into the local env variables */
	if (ft_strncmp(env_name, "USER", ft_strlen(env_name)) == 0)
	{
		var_value_len = ft_strlen(USER);
		var_key_len = ft_strlen("USER");
		old_value_len = ft_strlen(token_lst->value);
		new_value_len = (old_value_len - var_key_len) + var_value_len;
		
		new_value = (char *)malloc(sizeof(char) * (new_value_len + 1));
		if (new_value == NULL)
			return (0);
		ft_memcpy(new_value, token_lst->value, dolar_pos);

		ft_memcpy(&new_value[dolar_pos], USER, var_value_len);
		
		i = dolar_pos + var_value_len;
		j = dolar_pos + var_key_len + 1;
		int	off = old_value_len - var_key_len - dolar_pos;

		ft_memcpy(&new_value[i], &token_lst->value[j], off);

		free(token_lst->value);
		token_lst->value = new_value;

	}	
	free(env_name);
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
			if (ft_isalnum(token_lst->value[i + 1]))
				expand_in_quote(token_lst, i);
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
