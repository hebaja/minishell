/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:13:54 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/16 11:13:57 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_path(t_ms *ms)
{
	char	**paths;
	char	*env_path;

	env_path = get_var_value(ms->env_lst, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		clean_all(ms);
	return (paths);
}

void	init_ms(t_ms **ms, int argc, char **argv, char **envp)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
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

void	clean_prompt(t_ms *ms)
{
	free(ms->input);
	if (ms->token_lst)
		token_lst_clear(&ms->token_lst);
	if (ms->cmd_lst)
		cmd_lst_clear(&ms->cmd_lst);
	if (ms->paths)
		clean_matrix(&ms->paths);
	ms->input = readline(TERMINAL_PROMPT);
}

int	is_not_empty_input(char *value)
{
	while (*value)
	{
		if (!ft_isspace(*value))
			return (0);
		value++;
	}
	return (1);
}

int	run_minishell(t_ms *ms)
{
	if (!token_lst_build(ms) || !ms->token_lst)
		clean_prompt(ms);
	else if (is_not_empty_input(ms->input))
	{
		ms->status = 130;
		clean_prompt(ms);
	}
	else
	{
		if (!analyse_token_lst(ms))
			ms->status = 2;
		else
		{
			if (cmd_lst_build(ms))
				exec_cmd(ms);
			if (ms->is_exit || ms->input == NULL)
				return (0);
		}
		clean_prompt(ms);
	}
	signal(SIGINT, handle_sigint);
	return (1);
}
