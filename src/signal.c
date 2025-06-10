/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:54:38 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/09 18:25:02 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    handling_contrl(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
		exit_status(130);
	}
}

void    handling_contrl_exec(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		exit_status(130);
	}
}


void    handling_contrl_heor(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		exit_status(130);
		exit(130);
	}
}

int    ft_signal(void)
{
	signal(SIGINT, handling_contrl);
	return (0);
}

int    ft_signal_exec(void)
{
	signal(SIGINT, handling_contrl_exec);
	return (0);
}
