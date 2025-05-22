/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/05/07 14:58:44 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	builtin_echo(t_token *token_lst)
{
	if (token_lst->next && ft_strcmp(token_lst->next->value,"-n") == 0)
		ft_printf("%s", token_lst->next->next->value);
	else if (token_lst->next)
		ft_printf("%s\n", token_lst->next->value);
	else
		ft_printf("\n");
}

t_token	*token_lst_get_next(t_token *token_lst, t_token_type type)
{
	while (token_lst)
	{
		if (token_lst->type == type)
			return (token_lst->next);
		token_lst = token_lst->next;
	}
	return (NULL);
}

void	exec(t_token *token_lst)
{
	int	pid;
	char	*file_name;

	if (token_lst->type != BUILTIN_ECHO)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (token_lst->type == BUILTIN_ECHO)
		{
			file_name = token_lst_get_next(token_lst, REDIRECT_OUT)->value;
			

			int	fd;
			fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (fd == -1)
				ft_putstr_fd("Open error\n", 2);
			dup2(fd, STDOUT_FILENO);
			builtin_echo(token_lst);
			close(fd);
			exit(EXIT_SUCCESS);
		}
	}
}

/* TODO think about proper error msg when token integrity fails */
int	analyse_token_lst(t_token **token_lst)
{
	int	res;

	var_expansion(token_lst);
	quotes_var_expansion(token_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	conclude_parser(*token_lst);
	res = check_redirect(*token_lst);


	res = check_redirect(*token_lst);
	if (res == -1)
		ft_putstr_fd("Syntax error\n", 2);
	else
		exec(*token_lst);
	return (1);
}
