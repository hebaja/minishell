/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:20:37 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/26 17:53:13 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_prompt(t_token **token_lst, char **input)
{
	free(*input);
	token_lst_clear(token_lst);
	*input = readline(TERMINAL_PROMPT);
}

void	isCommandToken(t_token *token_head, t_env **env)
{
	if (token_head->type == BUILTIN_CD)
		builtin_cd(token_head);
	else if (token_head->type == BUILTIN_PWD)
		builtin_pwd();
	else if (token_head->type == BUILTIN_ECHO)
		builtin_echo(token_head);
	else if (token_head->type == BUILTIN_ENV)
		builtin_env(*env);
	else if (token_head->type == BUILTIN_EXPORT)
		builtin_export(token_head, *env);
	else if (token_head->type == BUILTIN_UNSET)
		builtin_unset(env, token_head);
	else if (token_head->type == BUILTIN_EXIT)
		builtin_exit(token_head);

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
		if (!token_lst_build(&token_lst, input) || !token_lst)
			clean_prompt(&token_lst, &input);
		else
		{
			analyse_token_lst(&token_lst);
			clean_prompt(&token_lst, &input);
		}
		isCommandToken(tokens_head, &environment_variables);
		token_lst_perform(&tokens_head);/* TODO Function to carry on the command */	
		free(input);
		token_lst_clear(&tokens_head);
	}
	if (token_lst)
		token_lst_clear(&token_lst);
	return (0);
}
