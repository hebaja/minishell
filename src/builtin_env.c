/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:05:22 by alda-sil          #+#    #+#             */
/*   Updated: 2025/04/14 21:30:57 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_env_keys(char **envp)
{
	t_env env_head;
	t_env env_tpm;

	while (*envp)
	{
		

		ft_printf("%s\n", *envp);
		envp++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	builtin_env_lts(envp);
	return (0);
}