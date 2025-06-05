/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:46:13 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/04 23:46:15 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	env_lst_size(t_env *env_lst)
{
	size_t	size;

	size = 0;
	while (env_lst)
	{
		size++;
		env_lst = env_lst->next;
	}
	return (size);
}

char	*build_env_sp(t_env *env)
{
	char	*env_str;
	size_t	env_size;
	size_t	key_size;
	size_t	val_size;

	key_size = ft_strlen(env->key);
	val_size = ft_strlen(env->value);
	env_size = key_size + val_size + 1;
	env_str = ft_calloc(env_size, sizeof(char));
	ft_memmove(env_str, env->key, ft_strlen(env->key));
	ft_memmove(&env_str[key_size], "=", 1);
	ft_memmove(&env_str[key_size + 1], env->value, val_size);
	return (env_str);
}

char	**split_env(t_env *env_lst)
{
	int		i;
	char	**env_sp;
	char	*env_tmp;
	size_t	size;

	i = 0;
	size = env_lst_size(env_lst);
	env_sp = (char **)malloc(sizeof(char *) * (size + 1));
	while (env_lst)
	{
		env_sp[i] = build_env_sp(env_lst);
		env_lst = env_lst->next;
		i++;
	}
	return (env_sp);
}

int	exec(t_cmd *cmd_lst, t_env *env_lst)
{
	char	**envp;
	int		pid;
	int		status;

	envp = split_env(env_lst);
	pid = fork();
	if (pid < 0)
	{
		perror("Failed to fork processes");
		return (0);
	}
	if (pid == 0)
	{
		execve(cmd_lst->path, cmd_lst->args, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (1);
}
