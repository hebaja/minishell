#include "../include/minishell.h"

void	clean_matrix(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	paths = NULL;
}

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

void	clean_all(t_ms *ms)
{
	if (ms->token_lst)
		token_lst_clear(&ms->token_lst);
	if (ms->cmd_lst)
		cmd_lst_clear(&ms->cmd_lst);
	if (ms->env_lst)
		env_lst_clear(&ms->env_lst);
	if (ms->paths)
		clean_matrix(ms->paths);
	free(ms->input);
	free(ms);
	ms = NULL;
}

void	clean_prompt(t_ms *ms)
{
	free(ms->input);
	if (ms->token_lst)
		token_lst_clear(&ms->token_lst);
	if (ms->cmd_lst)
		cmd_lst_clear(&ms->cmd_lst);
	if (ms->paths)
		clean_matrix(ms->paths);
	ms->input = readline(TERMINAL_PROMPT);
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
