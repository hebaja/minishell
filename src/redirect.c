#include "../include/minishell.h"

int 	create_heredoc(t_ms *ms, char *eof)
{
	char	*line;
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
	{
		signal(SIGINT, handle_heredoc_sigint);
		close(fd[0]);
		line = readline("> ");
		while (line)
		{
			if (ft_strcmp(line, eof) == 0)
				break;
			if (line && line[0])
				write(fd[1], line, ft_strlen(line));
			write(fd[1],"\n", 1);
			line = readline("> ");
		}
		close(fd[1]);
		close_redirect_all_fds(ms->cmd_lst);
		clean_all(ms);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	return (fd[0]);
}

void	set_redirect(t_ms *ms, t_token *curr_token, int *tmp_fd_out, int *tmp_fd_in)
{
	if (curr_token->next && (curr_token->type == REDIRECT_OUT
		|| curr_token->type == APPEND))
	{
		if (*tmp_fd_out > -1)
			close(*tmp_fd_out);
		if (curr_token->type == REDIRECT_OUT)
			*tmp_fd_out = open(curr_token->next->value, O_CREAT | O_WRONLY | O_TRUNC , 0644);
		else
			*tmp_fd_out = open(curr_token->next->value, O_CREAT | O_WRONLY | O_APPEND , 0644);
	}
	if (curr_token->next && (curr_token->type == REDIRECT_IN
		|| curr_token->type == HEREDOC))
	{
		if (*tmp_fd_in > -1)
			close(*tmp_fd_in);
		if (curr_token->type == REDIRECT_IN)
			*tmp_fd_in = open(curr_token->next->value, O_RDONLY , 0644);
		else
			*tmp_fd_in = create_heredoc(ms, curr_token->next->value);
			// *tmp_fd_in = open(curr_token->next->value, O_RDONLY, 0644);
	}
}

void	cmd_build_redirect(t_ms *ms, t_cmd *cmd, t_token *start_token, size_t cmd_size)
{
	int		tmp_fd_out;
	int		tmp_fd_in;
	t_token	*curr_token;
	
	tmp_fd_out = -1;
	tmp_fd_in = -1;
	cmd->fd_out = STDOUT_FILENO;
	cmd->fd_in = STDIN_FILENO;
	curr_token = start_token;
	while (cmd_size && curr_token)
	{
		set_redirect(ms, curr_token, &tmp_fd_out, &tmp_fd_in);
		cmd_size--;
		curr_token = curr_token->next;
	}
	if (tmp_fd_out > -1)
		cmd->fd_out = tmp_fd_out;
	if (tmp_fd_in > -1)
		cmd->fd_in = tmp_fd_in;
}

/*
int	is_not_redirect(t_token *token)
{
	if (token->type != REDIRECT_OUT && token->type != REDIRECT_IN
		&& token->type != APPEND && token->type && token->type != PIPE)
		return (1);
	return (0);
		
}

int	is_redir(t_token *token_lst)
{
	if (token_lst->type == REDIRECT_OUT || token_lst->type == REDIRECT_IN)
	{
		if (token_lst->next && ft_strlen(token_lst->value) == 1
			&& is_not_redirect(token_lst->next))
			return (1);
		return (-1);
	}
	if (token_lst->type == HEREDOC || token_lst->type == APPEND)
	{
		if (token_lst->next && ft_strlen(token_lst->value) == 2
			&& is_not_redirect(token_lst->next))
			return (1);
		return (-1);
	}
	return (0);
}

int	check_redirect(t_token *token_lst)
{
	int	res;

	res = token_lst_iterate_check(token_lst, is_redir);
	return (res);
}

void	redirect(t_token *token_lst)
{
	ft_printf("%d\n", check_redirect(token_lst));
}
*/
