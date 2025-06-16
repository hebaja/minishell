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

void    handle_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_ms(t_ms **ms, int argc, char **argv, char **envp)
{
	signal(SIGINT, handle_sigint);
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
	if (*ms->paths)
		clean_matrix(&ms->paths);
	ms->input = readline(TERMINAL_PROMPT);
}
