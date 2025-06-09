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

char	**split_path(t_env *env_lst)
{
	char	**paths;
	char	*env_path;

	env_path = get_var_value(env_lst, "PATH");
	paths = ft_split(env_path, ':');
	return (paths);
}

void	clean_all(t_token **token_lst, char **input, t_cmd **cmd_lst,
	char **split_paths)
{
	free(*input);
	if (*token_lst)
		token_lst_clear(token_lst);
	if (*cmd_lst)
		cmd_lst_clear(cmd_lst);
	if (split_paths)
		clean_matrix(split_paths);
}

void	clean_prompt(t_token **token_lst, char **input, t_cmd **cmd_lst,
	char **split_paths)
{
	free(*input);
	if (*token_lst)
		token_lst_clear(token_lst);
	if (*cmd_lst)
		cmd_lst_clear(cmd_lst);
	if (split_paths)
		clean_matrix(split_paths);
	*input = readline(TERMINAL_PROMPT);
}
