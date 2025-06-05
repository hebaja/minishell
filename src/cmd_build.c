#include "../include/minishell.h"

int	valid_abs_path(char *abs_pth)
{
	if (!abs_pth)
		return (0);
	if (access(abs_pth, F_OK) == 0 && access(abs_pth, X_OK) == 0)
		return (1);
	free(abs_pth);
	abs_pth = NULL;
	return (0);
}

char	*set_path(t_token *token_lst, char **paths)
{
	int		i;
	char	*tmp_pth;
	char	*abs_pth;

	i = -1;
	if (*token_lst->value != '/' && access(token_lst->value, F_OK) < 0)
	{
		while (paths[++i])
		{
			tmp_pth = ft_strjoin("/", token_lst->value);
			abs_pth = ft_strjoin(paths[i], tmp_pth);
			free(tmp_pth);
			if (valid_abs_path(abs_pth))
				return (abs_pth);
		}
	}
	abs_pth = ft_strdup(token_lst->value);
	return (abs_pth);
}

t_cmd	*cmd_build(t_token *start_token, size_t cmd_size, char **paths)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = split_token_value(start_token, cmd_size);
	cmd->path = set_path(start_token, paths);
	cmd->next = NULL;
	return (cmd);
}

int	append_cmd(t_cmd **cmd_lst, t_token *start_token, size_t cmd_size,
	char **paths)
{
	t_cmd	*new_cmd;

	if (*cmd_lst == NULL || cmd_lst == NULL)
	{
		new_cmd = cmd_build(start_token, cmd_size, paths);
		if (!new_cmd)
			return (0);
		*cmd_lst = new_cmd;
	}
	else
	{
		new_cmd = cmd_build(start_token, cmd_size, paths);
		if (!new_cmd)
			return (0);
		cmd_lst_add_back(cmd_lst, new_cmd);
	}
	return (1);
}

int	cmd_lst_build(t_cmd **cmd_lst, t_token *token_lst, char **paths)
{
	t_token	*start_token;
	int		cmd_size;

	start_token = token_lst;
	cmd_size = 0;
	while (token_lst)
	{
		if (token_lst->type == PIPE)
		{
			if(!append_cmd(cmd_lst, start_token, cmd_size, paths))
				return (0);
			start_token = token_lst->next;
			cmd_size = -1;
		}
		token_lst = token_lst->next;
		cmd_size++;
	}
	if(!append_cmd(cmd_lst, start_token, cmd_size, paths))
		return (0);
	print_cmd_lst(*cmd_lst);
	cmd_lst_clear(cmd_lst);
	return (1);
}
