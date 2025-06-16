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
	t_ms			*ms;
	unsigned char	status;
	int				sig_status;

	init_ms(&ms, argc, argv, envp);
	sig_status = 0;
	while (ms->input)
	{
		sig_status = sig_exit_status(-1);
		if (sig_status != -1)
			ms->status = sig_status;

		ms->paths = split_path(ms);
		if (ms->input)
			add_history(ms->input);
		if (!token_lst_build(ms) || !ms->token_lst)
			clean_prompt(ms);
		else
		{
			if (!analyse_token_lst(ms))
				ms->status = 2;
			else
			{
				cmd_lst_build(ms);
				exec_cmd(ms);
				if (ms->is_exit || ms->input == NULL)
					break ;
			}
			clean_prompt(ms);
		}
	}
	status = ms->status;
	clean_all(ms);
	ft_printf("exit\n");
	return (status);
}
