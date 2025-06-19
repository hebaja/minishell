#include "minishell_test.h"

char	**build_mock_envp(void)
{
	int		i;
	size_t	size;
	char	**mock_envp;
	char	buf[256];
	getcwd(buf, 256);
	char	*pwd = ft_strjoin("PWD=", buf);
	char	*oldpwd = ft_strjoin("OLDPWD=", buf);
	char	*user = getenv("USER");
	char	*env_user = ft_strjoin("USER=", user);
	char	*env_logname = ft_strjoin("LOGNAME=", user);
	char	*env_home = ft_strjoin("HOME=", getenv("HOME"));
	char	*env_path = ft_strjoin("PATH=", getenv("PATH"));
	
	char	*envp[] = {
		env_user,
		env_logname,
		env_home,
		pwd,
		oldpwd,
		env_path,
		"TERM=xterm-256color",
		"SHELL=/bin/zsh",
		"LANG=en_US.UTF-8",
		"LANGUAGE=en",
		"GIT_EDITOR=vim",
		"_=/usr/bin/env",
		NULL
	};
	i = -1;
	size = 0;
	while (envp[++i])
		size++;
	mock_envp = (char **)malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (envp[++i])
		mock_envp[i] = ft_strdup(envp[i]);
	mock_envp[i] = NULL;
	free(env_user);
	free(env_logname);
	free(env_home);
	free(pwd);
	free(oldpwd);
	free(env_path);
	return (mock_envp);
}

void	setup_alloc_mem(void)
{
	values = malloc(sizeof(char *) * 4);
	types = malloc(sizeof(char *) * 4);
}

void	init_ms_test()
{
	char	**mock_envp;
	int		i;

	ms = (t_ms *)malloc(sizeof(t_ms));
	mock_envp = build_mock_envp();
	if (!ms || !mock_envp)
		exit(EXIT_FAILURE);
	ms->token_lst = NULL;
	ms->env_lst = build_env_lst(0, NULL, mock_envp);
	ms->cmd_lst = NULL;
	ms->paths = NULL;
	ms->status = 0;
	ms->is_exit = 0;
	i = -1;
	while (mock_envp[++i])
		free(mock_envp[i]);
	free (mock_envp);
	mock_envp = NULL;
}

void redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

void	redirect_stdout(void)
{
	cr_redirect_stdout();
}

void	redirect_stderr(void)
{
	cr_redirect_stderr();
}

void	init_test(void)
{
	init_ms_test();
}

void	init_test_redirect_stderr(void)
{
	init_test();
	redirect_stderr();
}

void	init_test_redirect_stdout(void)
{
	init_test();
	redirect_stdout();
}

void	init_test_redirect_stdout_stderr(void)
{
	init_test();
	redirect_stdout();
	redirect_stderr();
}

void	init_test_alloc_mem(void)
{
	init_test();
	setup_alloc_mem();
}

void	clean_test(void)
{
	if (ms->token_lst != NULL)
		token_lst_clear(&ms->token_lst);
	if (ms->env_lst != NULL)
		env_lst_clear(&ms->env_lst);
	if (ms->paths != NULL)
		clean_split_path(ms->paths);
	if (ms->cmd_lst)
		cmd_lst_clear(&ms->cmd_lst);
	if (ms)
		free(ms);
	ms = NULL;
	unlink(">");
	unlink("<");
	unlink("|");
	unlink("out");
}

void	clean_split_path(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	paths = NULL;
}

char	**split_path_test(t_env *env_lst)
{
	char	**paths;
	char	*env_path;

	env_path = get_var_value(env_lst, "PATH");
	paths = ft_split(env_path, ':');
	return (paths);
}

char    *fetch_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == BACKGROUND)
		return ("BACKGROUND");
	if (type == WILDCARD_SOLO)
		return ("WILDCARD_SOLO");
	if (type == WILDCARD_JOIN)
		return ("WILDCARD_JOIN");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == DOLAR)
		return ("DOLAR");
	if (type == BUILTIN_ECHO)
		return ("BUILTIN_ECHO");
	if (type == BUILTIN_CD)
		return ("BUILTIN_CD");
	if (type == BUILTIN_ENV)
		return ("BUILTIN_ENV");
	if (type == BUILTIN_PWD)
		return ("BUILTIN_PWD");
	if (type == BUILTIN_EXIT)
		return ("BUILTIN_EXIT");
	if (type == BUILTIN_UNSET)
		return ("BUILTIN_UNSET");
	if (type == BUILTIN_EXPORT)
		return ("BUILTIN_EXPORT");
	if (type == SINGLE_QUOTED)
		return ("SINGLE_QUOTED");
	if (type == DOUBLE_QUOTED)
		return ("DOUBLE_QUOTED");
	return ("");
}

void	clean_values(char **values)
{
	while(*values)
	{
		free(*values);
		values++;
	}
	values = NULL;
}

char	**populate_values(int size, ...)
{
	int		i;
	char	**strs;
	va_list	args;

	i = -1;
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	va_start(args, size);
	while (++i < size)
		strs[i] = ft_strdup(va_arg(args, char *));
	va_end(args);
	strs[i] = NULL;
	return (strs);
}

char	*multi_str_join(int size, ...)
{
	int		i;
	char	*str;
	char	*tmp;
	int		str_len;
	int		offset;
	va_list	args;
	va_list copy_args;

	i = 0;
	str_len = 0;
	offset = 0;
	va_start(args, size);
	va_copy(copy_args, args);
	while (i < size)
	{	
		str_len += ft_strlen(va_arg(copy_args, char *));
		i++;
	}
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	i = 0;
	while (i < size)
	{
		tmp = va_arg(args, char *);
		ft_memmove(&str[offset], tmp, ft_strlen(tmp));
		offset += ft_strlen(tmp);
		i++;
	}
	va_end(args);
	va_end(copy_args);
	str[offset] = '\0';
	return (str);
}

char	**split_token_lst(t_token *token_lst)
{
	char	**split_values;
	size_t	size;
	int		i;

	size = token_lst_size(token_lst);
	split_values = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (token_lst)
	{
		split_values[i] = ft_strdup(token_lst->value);
		token_lst = token_lst->next;
		i++;
	}
	split_values[i] = NULL;
	return split_values;
}

char	**fetch_tokens_type_list(t_token *token_lst)
{
	char	**tokens_type_list;
	char	*type_str;

	tokens_type_list = (char **)malloc(sizeof(char *) * (token_lst_size(token_lst) + 1));
	i = 0;
	while (token_lst)
	{
		size = 0;
		type_str = fetch_token_type(token_lst->type);
		size = ft_strlen(type_str);
		tokens_type_list[i] = strdup(type_str);
		token_lst = token_lst->next;
		i++;
	}
	return (tokens_type_list);
}

void	unquoted_value_test(t_token *token_lst, char *value, char quote)
{
	char	*unquoted;

	size = 0;
	value++;
	while (value[size] != quote && value[size])
		size++;
	size++;
	unquoted = (char *)malloc(sizeof(char) * (size));
	ft_strlcpy(unquoted, value, size);
	cr_assert_str_eq(token_lst->value, unquoted);
}

void	test_token_lst(t_token *token_lst, char *value, char *type)
{
	if (*value == '\'' || *value == '\"')
		unquoted_value_test(token_lst, value, *value);
	else
		cr_assert_str_eq(token_lst->value, value);
	cr_assert_str_eq(fetch_token_type(token_lst->type), type);
}

void	test_lst(t_token *token_lst, char **values, char **types)
{
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	cr_assert_null(token_lst);
	token_lst_clear(&token_lst);
}

void wait_for_pids_test(t_ms *ms)
{
	t_cmd	*cmd_curr;

	cmd_curr = ms->cmd_lst;
	while (cmd_curr)
	{
		waitpid(cmd_curr->pid, &ms->status, 0);
		char	*message;

		if (WIFEXITED(ms->status))
		{
			if (WEXITSTATUS(ms->status))
			{
				ms->status = WEXITSTATUS(ms->status);
				if (ms->status == 127)
				{
					message = ft_strjoin(cmd_curr->path, ": command not found\n");
					ft_putstr_fd(message, 2);
					free(message);
				}
				if (errno == 0)
					ms->status -= 1;
			}
		}
		cmd_curr = cmd_curr->next;
	}
}

void	mock_input(char *input)
{
	int pipe_fd[2];

    pipe(pipe_fd);
    write(pipe_fd[1], input, ft_strlen(input));
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
}

void	usual_flow(t_ms *ms)
{
	var_expansion(&ms->token_lst, ms->env_lst);
	quotes_var_expansion(&ms->token_lst, ms->env_lst);
	quote_removal(ms->token_lst);
	token_joining(&ms->token_lst);
	ms->paths = split_path_test(ms->env_lst);
	conclude_parser(ms);
	cmd_lst_build(ms);
}
