#include "../include/minishell.h"

char	**split_path(t_ms *ms)
{
	char	**paths;
	char	*env_path;

	env_path = get_var_value(ms->env_lst, "PATH");
	paths = ft_split(env_path, ':');
	if (!paths)
		clean_all(ms);
	return (paths);
}

void	init_ms(t_ms **ms, int argc, char **argv, char **envp)
{
	*ms = (t_ms *)malloc(sizeof(t_ms));
	if (!ms)
		exit(EXIT_FAILURE);
	(*ms)->token_lst = NULL;
	(*ms)->env_lst = build_env_lst(argc, argv, envp);
	(*ms)->cmd_lst = NULL;
	(*ms)->paths = NULL;
	(*ms)->status = 0;
	(*ms)->is_exit = 0;
	using_history();
	(*ms)->input = readline(TERMINAL_PROMPT);
}

void wait_for_pids(t_ms *ms)
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
