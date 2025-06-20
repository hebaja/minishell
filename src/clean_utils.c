/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:59:45 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 20:01:17 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_matrix(char ***paths)
{
	int	i;

	i = -1;
	while ((*paths)[++i])
		free((*paths)[i]);
	free(*paths);
	*paths = NULL;
}

void	clean_all(t_ms *ms)
{
	if (ms->token_lst)
		token_lst_clear(&ms->token_lst);
	if (ms->cmd_lst)
		cmd_lst_clear(&ms->cmd_lst);
	if (ms->env_lst)
		env_lst_clear(&ms->env_lst);
	if (ms->paths)
		clean_matrix(&ms->paths);
	free(ms);
	ms = NULL;
}
