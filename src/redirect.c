/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:46:08 by alda-sil          #+#    #+#             */
/*   Updated: 2025/06/09 21:57:55 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int 	create_heredoc(char *eof)
{
	char	*line;
	int		fd[2];


	pipe(fd);
	signal(SIGINT, handling_contrl_heor);
	line = readline(">");
	while (line)
	{
		if (ft_strcmp(line, eof) == 0)
			break;
		if (line && line[0])
			write(fd[1], line, ft_strlen(line));
		write(fd[1],"\n", 1);
		line = readline(">");
	}
	return (fd[1]);
}

void	create_redirect(t_token **token_lst)
{
	t_token *current;
	int		fd_in;
	int		fd_out;


	fd_in = -1;
	fd_out = -1;
	current = *token_lst;
	while (current)
	{
		if (current->type == REDIRECT_IN || current->type == HEREDOC)
		{
			if (fd_in != -1)
				close(fd_in);
			if (current->type == REDIRECT_IN)
				fd_in = open(current->next->value, O_RDONLY, 0644);
			else
				fd_in = create_heredoc(current->next->value);	
			current->fd = fd_in;
		}
		else if (current->type == REDIRECT_OUT || current->type == APPEND)
		{	
			if (fd_out != -1)
				close(fd_out);
			if (current->type == REDIRECT_OUT)		
				fd_out = open(current->next->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				fd_out = open(current->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
			current->fd = fd_out;
		}
		current = current->next;
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}
