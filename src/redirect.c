/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alda-sil <alda-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:38:36 by alda-sil          #+#    #+#             */
/*   Updated: 2025/05/27 19:52:27 by alda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int 	create_heredoc(char *eof)
{
	char	*line;
	int		fd[2];


	pipe(fd);
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
	return (fd[0]);
}


void	create_redicter(t_token **token_lst)
{
	t_token **current;

	current = token_lst;
	while (*current)
	{
		if ((*current)->type == REDIRECT_IN)
			(*current)->fd = open((*current)->next->value, O_RDONLY, 0644);
		else if ((*current)->type == REDIRECT_OUT)
			(*current)->fd = open((*current)->next->value, O_CREAT | O_RDWR, 0644);
		else if ((*current)->type == APPEND)
			(*current)->fd = open((*current)->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		else if ((*current)->type == HEREDOC)
			(*current)->fd = create_heredoc((*current)->next->value);	
		(*current) = (*current)->next;
	}
	
}
