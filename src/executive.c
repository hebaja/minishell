/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:53:13 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/28 19:56:00 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	execute(t_token *token_lst)
{
	pid_t pid;
	t_token	*tmp;
	t_token *start;

	pid = fork();
	tmp = token_lst;
	start = tmp;
	if (pid < 0)
	{
		perror("ERROR: pid failed");
		return ;
	}
	if (pid == 0)
	{
		char	*argv[100];
		int		i;

		i = 0;
		while (tmp)
		{
			if (ft_strcmp(tmp->value, "|") == 0)
			{
				while (start && ft_strcmp(start->value, "|") != 0)
				{
					printf("token: %s\n", start->value);
					argv[i++] = start->value;
					start = start->next;
				}
				argv[] = NULL;
				start = tmp->next->next;		
			}
			tmp = tmp->next;
		}	
	}
}
