#include "../include/minishell.h"

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
