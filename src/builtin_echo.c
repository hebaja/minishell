/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:18:55 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/14 20:25:27 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*build_token()
{
	t_token *tokens_head;
	t_token *token_flag;
	t_token *token_word;

	tokens_head = token_build("echo", 4);
	//token_flag = token_build("-n", 2);
	token_word = token_build("teste", 5);
	//token_lst_add_back(&tokens_head, token_flag);
	token_lst_add_back(&tokens_head, token_word);
	return tokens_head;
}

void	builtin_echo()
{
	t_token	*token_lst;
	t_token *current;
	
	token_lst = build_token();
	current = token_lst->next;

	print_tokens(token_lst);
	if (ft_strcmp(current->value,"-n") == 0)
	{
		if (current->next->type == WORD)
			ft_printf("%s", token_lst->next->next->value);
		return ;
	}
	else if (current->type == WORD)
	{
		ft_printf("%s\n", token_lst->next->value);
		return ;
	}
	else
		ft_printf("\n");
}

int	main()
{
	builtin_echo();
	return (0);
}