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

void	init_ms(t_ms **ms, int argc, char **argv, char **envp)
{
	*ms = (t_ms *)malloc(sizeof(t_ms));
	if (!ms)
		exit(EXIT_FAILURE);
	(*ms)->token_lst = NULL;
	(*ms)->env_lst = build_env_lst(argc, argv, envp);
	(*ms)->cmd_lst = NULL;
	(*ms)->paths = NULL;
	(*ms)->status = 0;
	(*ms)->is_exit = 0;
	using_history();
	(*ms)->input = readline(TERMINAL_PROMPT);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	int		status;

	init_ms(&ms, argc, argv, envp);
	while (ms->input)
	{
		ms->paths = split_path(ms);
		if (ms->input)
			add_history(ms->input);
		if (!token_lst_build(ms, ms->input) || !ms->token_lst)
			clean_prompt(ms);
		else
		{
			if (analyse_token_lst(ms))
			{
				cmd_lst_build(ms, ms->token_lst);
				exec_cmd(ms, ms->cmd_lst);
				if (ms->is_exit)
					break ;
			}
			clean_prompt(ms);
		}
	}
	status = ms->status;
	clean_all(ms);
	return (status);
}
