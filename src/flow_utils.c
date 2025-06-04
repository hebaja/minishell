#include "../include/minishell.h"

void	clean_split_path(char **paths)
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

void	clean_prompt(t_token **token_lst, char **input, char **split_paths)
{
	free(*input);
	token_lst_clear(token_lst);
	clean_split_path(split_paths);
	*input = readline(TERMINAL_PROMPT);
}
