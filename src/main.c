/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:20:37 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/26 19:18:40 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_prompt(t_token **token_lst, char **input)
{
	free(*input);
	token_lst_clear(token_lst);
	*input = readline(TERMINAL_PROMPT);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token *token_lst;
	t_env	*env_lst;

	env_lst = build_env_lst(argc, argv, envp);
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
			if (analyse_token_lst(&token_lst, env_lst))
			{
				if (token_lst->type == BUILTIN_ECHO)
					builtin_echo(token_lst);
				if (token_lst->type == BUILTIN_ENV)
					builtin_env(env_lst);
				if (token_lst->type == BUILTIN_CD)
					builtin_cd(token_lst, env_lst);
				if (token_lst->type == BUILTIN_PWD)
					builtin_pwd();
				if (token_lst->type == BUILTIN_EXPORT)
					builtin_export(token_lst, env_lst);
				if (token_lst->type == BUILTIN_UNSET)
					builtin_unset(token_lst, &env_lst);
				if (token_lst->type == BUILTIN_EXIT)
					builtin_exit(&token_lst, &env_lst);
			}
			clean_prompt(&token_lst, &input);
		}
	}
	if (token_lst)
		token_lst_clear(&token_lst);
	if (env_lst)
		env_lst_clear(&env_lst);
	return (0);
}
