#include "../include/minishell.h"

size_t	get_rebuilt_cmd_size(t_token *start_token)
{
	int		inverse_flag;
	size_t	size;
	t_token	*curr_token;

	inverse_flag = 0;
	size = 0;
	curr_token = start_token;
	while (curr_token)
	{
		if (is_redirect(curr_token->type)
			&& (curr_token->next && !is_redirect(curr_token->next->type))
			&& (curr_token->next->next
			&& !is_redirect(curr_token->next->next->type)))
		{
			inverse_flag = 1;
			curr_token = curr_token->next->next;
		}
		curr_token = curr_token->next;
		if (inverse_flag)
			size++;
	}
	return (size);
}

t_token	*get_target_token(t_token *start_token)
{
	t_token	*curr_token;
	t_token	*target_token;

	curr_token = start_token;
	target_token = NULL;
	while (curr_token)
	{
		if (is_redirect(curr_token->type)
			&& (curr_token->next && !is_redirect(curr_token->next->type))
			&& (curr_token->next->next
			&& !is_redirect(curr_token->next->next->type)))
		{
			target_token = curr_token->next->next;
			break ;
		}
		curr_token = curr_token->next;
	}
	return (target_token);
}

int	cmd_rebuild(t_ms *ms, t_token *start_token, char **paths)
{
	t_token	*target_token;
	t_cmd	*last_cmd;
	size_t	size;

	size = 0;
	target_token = get_target_token(start_token);
	if (target_token)
	{
		size = get_rebuilt_cmd_size(start_token);
		if (size == 0)
			return (1);
		last_cmd = cmd_lst_last(ms->cmd_lst);
		clean_matrix(&last_cmd->args);
		free(last_cmd->path);
		last_cmd->args = split_token_value(target_token, size);
		last_cmd->main_type = target_token->type;
		last_cmd->path = set_path(target_token, paths);
		return (1);
	}
	return (1);
}
