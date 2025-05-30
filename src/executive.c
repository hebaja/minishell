/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:53:13 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/29 21:06:12 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void	son_progress(t_token *token_lst, t_sent **sent)
{

}
*/	

void	execute(t_token *token_lst)
{
	//pid_t pid;
	t_token	*tmp;
	t_token *start;
	t_sent	*sent;
	int		i;

	i = 0;
	sent = NULL;
	//pid = fork();
	tmp = token_lst;
	start = tmp;

	sent->args = malloc(sizeof(t_sent));
	/*
	if (pid < 0)
	{
		perror("ERROR: pid failed");
		return ;
	}
	if (pid == 0)
	{

		//son_progress();
	
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
				argv[i] = NULL;
				start = tmp->next->next;		
			}
			tmp = tmp->next;
			
	}*/
	
	//else
	//{
		while (tmp)
		{
			if (ft_strcmp(tmp->value, "|") == 0)
			{
				while (start && ft_strcmp(start->value, "|") != 0)
				{
					sent->args[i++] = start->value;
					start = start->next;
					printf("sent: %s\n", *sent->args);
					i = 0;
				}
				sent->args[i] = NULL;
				start = tmp->next->next;		
			}
			tmp = tmp->next;
		}	
	//}
}	
