/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:50:58 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 19:51:00 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_heredoc_child(t_ms *ms, int fd[2], char *eof)
{
	char	*line;

	signal(SIGINT, handle_heredoc_sigint);
	close(fd[0]);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, eof) == 0)
			break ;
		if (line && line[0])
			write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		line = readline("> ");
	}
	close(fd[1]);
	close_redirect_all_fds(ms->cmd_lst);
	clean_all(ms);
	exit(EXIT_SUCCESS);
}

int	create_heredoc(t_ms *ms, char *eof)
{
	int		pid;
	int		fd[2];
	int		status;

	signal(SIGINT, SIG_IGN);
	if (pipe(fd) < 0)
	{
		perror("Failed to create heredoc pipe");
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork heredoc processes");
		return (0);
	}
	if (pid == 0)
		run_heredoc_child(ms, fd, eof);
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	return (fd[0]);
}

void	check_file_fd(int fd, char *value)
{
	if (fd < 0)
		perror(value);
}

void	set_redirect(t_ms *ms, t_token *curr_token, int *tmp_fd_out,
		int *tmp_fd_in)
{
	if (curr_token->next && (curr_token->type == REDIRECT_IN
			|| curr_token->type == HEREDOC))
	{
		if (*tmp_fd_in > -1)
			close(*tmp_fd_in);
		if (curr_token->type == REDIRECT_IN)
			*tmp_fd_in = open(curr_token->next->value, O_RDONLY, 0644);
		else
			*tmp_fd_in = create_heredoc(ms, curr_token->next->value);
		check_file_fd(*tmp_fd_in, curr_token->next->value);
	}
	if (curr_token->next && (curr_token->type == REDIRECT_OUT
			|| curr_token->type == APPEND))
	{
		if (*tmp_fd_out > -1)
			close(*tmp_fd_out);
		if (curr_token->type == REDIRECT_OUT)
			*tmp_fd_out = open(curr_token->next->value,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			*tmp_fd_out = open(curr_token->next->value,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		check_file_fd(*tmp_fd_out, curr_token->next->value);
	}
}

void	cmd_build_redirect(t_ms *ms, t_cmd *cmd, t_token *start_token,
		size_t cmd_size)
{
	int		tmp_fd_in;
	int		tmp_fd_out;
	t_token	*curr_token;

	tmp_fd_in = -1;
	tmp_fd_out = -1;
	cmd->fd_out = STDOUT_FILENO;
	cmd->fd_in = STDIN_FILENO;
	curr_token = start_token;
	while (cmd_size && curr_token)
	{
		set_redirect(ms, curr_token, &tmp_fd_out, &tmp_fd_in);
		cmd_size--;
		curr_token = curr_token->next;
	}
	if (tmp_fd_in > -1)
		cmd->fd_in = tmp_fd_in;
	if (tmp_fd_out > -1)
		cmd->fd_out = tmp_fd_out;
}
