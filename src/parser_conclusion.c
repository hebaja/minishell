#include "../include/minishell.h"

int	is_redirect(t_token *token)
{
	if (token->type == REDIRECT_OUT || token->type == REDIRECT_IN
		|| token->type == APPEND || token->type == PIPE)
		return (1);
	return (0);		
}

int	redirect_validate(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->type == REDIRECT_IN || token_lst->type == REDIRECT_OUT
			|| token_lst->type == PIPE)
		{
			if (!token_lst->next || ft_strlen(token_lst->value) != 1
				|| is_redirect(token_lst->next))
			{
				ft_putstr_fd("Syntax error\n", 2);
				return (0);
			}
		}
		if (token_lst->type == HEREDOC || token_lst->type == APPEND)
		{
			if (!token_lst->next || ft_strlen(token_lst->value) != 2
				|| is_redirect(token_lst->next))
			{
				ft_putstr_fd("Syntax error\n", 2);
				return (0);
			}
		}
		token_lst = token_lst->next;
	}
	return (1);
}

int	check_token_integrity(t_token *token_lst)
{
	while (token_lst)
	{
		if (token_lst->value == NULL)
		{
			ft_putstr_fd("Problem building tokens\n", 2);
			return (0);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

void	builtin_recheck(t_token *token)
{
	if (token->value)
		define_type_builtin(token->value, &token->type);
}

int	conclude_parser(t_ms *ms)
{
	token_lst_iterate(ms->token_lst, builtin_recheck);
	if (!check_token_integrity(ms->token_lst))
		return (0);
	if (!redirect_validate(ms->token_lst))
		return (0);
	return (1);
}
