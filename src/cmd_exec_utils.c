#include "../include/minishell.h"

void	wait_for_pids(t_ms *ms)
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

void	close_fds_parent(t_ms *ms)
{
	t_cmd	*cmd_curr;

	cmd_curr = ms->cmd_lst;
	while (cmd_curr)
	{
		if (cmd_curr->is_piped)
		{
			close(cmd_curr->fds[0]);
			close(cmd_curr->fds[1]);
		}
		cmd_curr = cmd_curr->next;
	}
}

void	exec_child_builtin(t_ms *ms, t_cmd *cmd, char **envp)
{
	exec_builtin(cmd, ms);
	clean_all(ms);
	clean_matrix(&envp);
	close(STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	exec_child_execve(t_ms *ms, t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->args, envp);
	clean_all(ms);
	clean_matrix(&envp);
	exit(127);
}
