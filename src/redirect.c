// #include "../include/minishell.h"

// int	is_not_redirect(t_token *token)
// {
// 	if (token->type != REDIRECT_OUT && token->type != REDIRECT_IN
// 		&& token->type != APPEND && token->type && token->type != PIPE)
// 		return (1);
// 	return (0);
// 		
// }

// int	is_redirect(t_token *token_lst)
// {
// 	if (token_lst->type == REDIRECT_OUT || token_lst->type == REDIRECT_IN)
// 	{
// 		if (token_lst->next && ft_strlen(token_lst->value) == 1
// 			&& is_not_redirect(token_lst->next))
// 			return (1);
// 		return (-1);
// 	}
// 	if (token_lst->type == HEREDOC || token_lst->type == APPEND)
// 	{
// 		if (token_lst->next && ft_strlen(token_lst->value) == 2
// 			&& is_not_redirect(token_lst->next))
// 			return (1);
// 		return (-1);
// 	}
// 	return (0);
// }

// int	check_redirect(t_token *token_lst)
// {
// 	int	res;

// 	res = token_lst_iterate_check(token_lst, is_redirect);
// 	return (res);
// }
