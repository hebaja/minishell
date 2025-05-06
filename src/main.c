/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:20:37 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/06 14:57:37 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	isCommandToken(t_token *token_head, t_env *env)
{
	if (token_head->type == BUILTIN_CD)
		builtin_cd(token_head);
	else if (token_head->type == BUILTIN_PWD)
		builtin_pwd();
	else if (token_head->type == BUILTIN_ECHO)
		builtin_echo(token_head);
	else if (token_head->type == BUILTIN_ENV)
		builtin_env(env);
	else if (token_head->type == BUILTIN_EXPORT)
		builtin_export(token_head, env);

}

int	main(int argc, char **argv , char **envp)
{
	char	*input;
	t_token	*tokens_head;
	t_env	*environment_variables;


	tokens_head = NULL;
	(void)argc;
	(void)argv;
	using_history();
	input = readline(TERMINAL_PROMPT);
	environment_variables = fn_enviroment_variables(envp);
	while (input)
	{
		if (ft_strncmp(input, "quit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (input)
			add_history(input);
		token_lst_build(&tokens_head, input);
		if (!tokens_head)
		{
			free(input);
			break ;
		}
		isCommandToken(tokens_head, environment_variables);
		token_lst_perform(&tokens_head);/* TODO Function to carry on the command */	
		free(input);
		token_lst_clear(&tokens_head);
		input = readline(TERMINAL_PROMPT);
	}
	if (tokens_head)
		token_lst_clear(&tokens_head);
	return (0);
}
