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
		add_history(ms->input);
		sig_status = sig_exit_status(-1);
		ms->paths = split_path(ms);
		if (sig_status != -1)
			ms->status = sig_status;
		if (!run_minishell(ms))
			break ;
	}
	status = ms->status;
	clean_all(ms);
	ft_printf("exit\n");
	return (status);
}
