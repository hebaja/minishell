/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:20:37 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/03 20:20:41 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens_head;

	tokens_head = NULL;
	input = readline(TERMINAL_PROMPT);
	while (input)
	{
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (!token_lst_build(&tokens_head, input))
		{
			free(input);
			break ;
		}
		print_tokens(tokens_head);
		free(input);
		token_lst_clear(&tokens_head);
		input = readline(TERMINAL_PROMPT);
	}
	if (tokens_head)
		token_lst_clear(&tokens_head);
	return (0);
}
