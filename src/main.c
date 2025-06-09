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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token *token_lst;
	t_env	*env_lst;
	t_cmd	*cmd_lst;
	char	**paths;
	int		status_ctrl[2];

	env_lst = build_env_lst(argc, argv, envp);
	token_lst = NULL;
	cmd_lst = NULL;
	status_ctrl[0] = 0;
	status_ctrl[1] = 0;
	using_history();
	input = readline(TERMINAL_PROMPT);
	while (input)
	{
		paths = split_path(env_lst);
		if (input)
			add_history(input);
		if (!token_lst_build(&token_lst, input) || !token_lst)
			clean_prompt(&token_lst, &input, &cmd_lst, paths);
		else
		{
			if (analyse_token_lst(&token_lst, env_lst))
			{
				cmd_lst_build(&cmd_lst, token_lst, paths);
				exec_cmd(cmd_lst, env_lst, status_ctrl);
				if (status_ctrl[1] == 1)
					break ;
			}
			clean_prompt(&token_lst, &input, &cmd_lst, paths);
		}
	}
	env_lst_clear(&env_lst);
	clean_all(&token_lst, &input, &cmd_lst, paths);
	return (status_ctrl[0]);
}
