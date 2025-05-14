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

void	clean_prompt(t_token **token_lst, char **input)
{
	free(*input);
	token_lst_clear(token_lst);
	*input = readline(TERMINAL_PROMPT);
}

int	main(void)
{
	char	*input;
	t_token	*token_lst;

	token_lst = NULL;
	using_history();
	input = readline(TERMINAL_PROMPT);
	while (input)
	{
		if (ft_strncmp(input, "quit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (input)
			add_history(input);
		if (!token_lst_build(&token_lst, input) || !token_lst)
			clean_prompt(&token_lst, &input);
		else
		{
			analyse_token_lst(&token_lst);
			clean_prompt(&token_lst, &input);
		}
	}
	if (token_lst)
		token_lst_clear(&token_lst);
	return (0);
}
