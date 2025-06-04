#include "../include/minishell.h"

void	print_cmd_lst(t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	while(cmd_lst)
	{
		while (cmd_lst->args[i])
		{
			ft_printf("%s -> ", cmd_lst->args[i]);
			i++;
		}
		cmd_lst = cmd_lst->next;
		i = 0;
		ft_printf("\n");
	}
}

void	cmd_lst_iterate(t_cmd *cmd_lst,	void (*func)(t_cmd *))
{
	t_cmd	*next_cmd;

	if (cmd_lst == NULL)
		return ;
	while (cmd_lst)
	{
		next_cmd = cmd_lst->next;
		func(cmd_lst);
		cmd_lst = next_cmd;
	}
}

void	cmd_clear(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd->args[++i])
		free(cmd->args[i]);
	free(cmd->args);
	cmd->args = NULL;
	// clear path
	free(cmd);
	cmd = NULL;
}

void	cmd_lst_clear(t_cmd **cmd_lst)
{
	if (cmd_lst != NULL)
		cmd_lst_iterate(*cmd_lst, cmd_clear);
	*cmd_lst = NULL;
}

t_cmd	*cmd_lst_last(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		if (cmd_lst->next == NULL)
			break ;
		cmd_lst = cmd_lst->next;
	}
	return (cmd_lst);
}

void	cmd_lst_add_back(t_cmd **cmd_lst, t_cmd *cmd)
{
	if (*cmd_lst == NULL)
		*cmd_lst = cmd;
	else
		cmd_lst_last(*cmd_lst)->next = cmd;
}

/* TODO Not sure if this is necessary */
char	*set_arg(t_token *token_lst)
{
	char	*arg;

	if (token_lst->type != SINGLE_QUOTED && token_lst->type != DOUBLE_QUOTED)
		arg = ft_strtrim(token_lst->value, " \t");
	else
		arg = ft_strdup(token_lst->value);
	return (arg);
}

char	**split_token_value(t_token *token_lst, size_t cmd_size)
{
	int		i;
	char	**args;

	i = 0;
	args = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	while (cmd_size)
	{
		args[i] = set_arg(token_lst);
		token_lst = token_lst->next;
		cmd_size--;
		i++;
	}
	args[i] = NULL;
	return (args);
}

// char	set_path(t_token *token_lst)
// {
// 	if (*token_lst->value != '/' && access(token_lst->value, F_OK) < 0)
// 	{
// 		
// 	}
// }

t_cmd	*cmd_build(t_token *start_token, size_t cmd_size)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = split_token_value(start_token, cmd_size);
	cmd->path = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	append_cmd(t_cmd **cmd_lst, t_token *start_token, size_t cmd_size)
{
	t_cmd	*new_cmd;

	if (*cmd_lst == NULL)
	{
		new_cmd = cmd_build(start_token, cmd_size);
		if (!new_cmd)
			return (0);
		*cmd_lst = new_cmd;
	}
	else
	{
		new_cmd = cmd_build(start_token, cmd_size);
		if (!new_cmd)
			return (0);
		cmd_lst_add_back(cmd_lst, new_cmd);
	}
	return (1);
}

int	cmd_lst_build(t_token *token_lst)
{
	t_token	*start_token;
	t_cmd	*cmd_lst;
	int		cmd_size;

	start_token = token_lst;
	cmd_lst = NULL;
	cmd_size = 0;
	while (token_lst)
	{
		if (token_lst->type == PIPE)
		{
			if(!append_cmd(&cmd_lst, start_token, cmd_size))
				return (0);
			start_token = token_lst->next;
			cmd_size = -1;
		}
		token_lst = token_lst->next;
		cmd_size++;
	}
	if(!append_cmd(&cmd_lst, start_token, cmd_size))
		return (0);
	print_cmd_lst(cmd_lst);
	cmd_lst_clear(&cmd_lst);
	return (1);
}
