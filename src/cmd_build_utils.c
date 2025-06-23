/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:33:17 by hebatist          #+#    #+#             */
/*   Updated: 2025/06/19 20:33:20 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_fds(t_cmd *cmd)
{
	if (pipe(cmd->fds) < 0)
	{
		perror("Create pipe error");
		return (0);
	}
	cmd->is_piped = 1;
	return (1);
}

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

char	*set_path(t_token *token, char **paths)
{
	int		i;
	char	*tmp_pth;
	char	*abs_pth;

	i = -1;
	if (*token->value != '/' && access(token->value, F_OK) < 0)
	{
		while (paths[++i])
		{
			tmp_pth = ft_strjoin("/", token->value);
			abs_pth = ft_strjoin(paths[i], tmp_pth);
			free(tmp_pth);
			if (valid_abs_path(abs_pth))
				return (abs_pth);
		}
	}
	abs_pth = ft_strdup(token->value);
	return (abs_pth);
}



