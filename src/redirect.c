/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:46:08 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/17 19:58:50 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	create_redirect(t_token **token_lst)
{
	t_token *current;
	int		fd_in;
	int		fd_out;
	t_token	*tmp;


	fd_in = -1;
	fd_out = -1;
	current = *token_lst;
	while (current)
	{
		if ((current->type == REDIRECT_IN || current->type == HEREDOC) && current->next)
		{
			if (fd_in != -1)
				close(fd_in);
			if (current->type == REDIRECT_IN)
				fd_in = open(current->next->value, O_RDONLY, 0644);
			//else
			//	fd_in = create_heredoc(current->next->value);	
		}
		else if ((current->type == REDIRECT_OUT || current->type == APPEND) && current->next)
		{	
			if (fd_out != -1)
				close(fd_out);
			if (current->type == REDIRECT_OUT)		
				fd_out = open(current->next->value, O_CREAT | O_WRONLY | O_TRUNC , 0644);
			else
				fd_out = open(current->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		current = current->next;
	}
	
	tmp = *token_lst;
	while (tmp)
	{
		tmp->fd_in = fd_in;
		tmp->fd_out = fd_out;
		tmp = tmp->next;
	}
}
