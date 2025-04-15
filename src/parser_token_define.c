/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_define.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:36:41 by hebatist          #+#    #+#             */
/*   Updated: 2025/04/14 01:36:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	syntax_check(char *value, size_t size)
{
	if (ft_strnstr(value, " ", size + 1) || ft_strnstr(value, "&", size + 1)
		|| ft_strlen(value) == size)
		return (1);
	return (0);
}

/* TODO after here, if word is the sabe as builting, show syntax error*/
int	define_type_builtin(char *value, t_token_type *type)
{
	int	res;

	res = 1;
<<<<<<< HEAD
	if (ft_strncmp(value, "echo", 4) == 0 && syntax_check(value, 4))
	{
		*type = BUILTIN_ECHO;
	}
=======
	if (ft_strncmp(value, "echo", 4) == 0)
		*type = BUILTIN_ECHO;
>>>>>>> e03dc3b (feat: 🎸 Parser - Lexical Analysis)
	else if (ft_strncmp(value, "cd", 2) == 0)
		*type = BUILTIN_CD;
	else if (ft_strncmp(value, "pwd", 3) == 0)
		*type = BUILTIN_PWD;
	else if (ft_strncmp(value, "export", 6) == 0)
		*type = BUILTIN_EXPORT;
	else if (ft_strncmp(value, "unset", 5) == 0)
		*type = BUILTIN_UNSET;
	else if (ft_strncmp(value, "env", 3) == 0)
		*type = BUILTIN_ENV;
	else if (ft_strncmp(value, "exit", 4) == 0)
		*type = BUILTIN_EXIT;
	else
		res = 0;
	return (res);
}

int	define_type_more(char *value, t_token_type *type)
{
	int	res;

	res = 1;
	if (ft_strncmp(value, ">>", 2) == 0)
		*type = APPEND;
	else if (ft_strncmp(value, "<<", 2) == 0)
		*type = HEREDOC;
	else if (ft_strncmp(value, ">", 1) == 0)
		*type = REDIRECT_OUT;
	else if (ft_strncmp(value, "<", 1) == 0)
		*type = REDIRECT_IN;
	else if (ft_strncmp(value, "\'", 1) == 0)
		*type = SINGLE_QUOTED;
	else if (ft_strncmp(value, "\"", 1) == 0)
		*type = DOUBLE_QUOTED;
	else
		res = 0;
	return (res);
}

/* * NEEDS SPACE RIGHT BEFORE */
/* $ NEEDS LETTER RIGHT AFTER */
t_token_type	define_type(char *value)
{
	t_token_type	type;

	if (ft_strncmp(value, "-", 1) == 0)
	{
		if (ft_strncmp(value + 1, " ", 1) != 0)
			return (FLAG);
	}
	else if (ft_strncmp(value, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(value, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(value, "&", 1) == 0)
		return (BACKGROUND);
	else if (ft_strncmp(value, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(value, "*", 2) == 0)
		return (WILDCARD);
	else if (ft_strncmp(value, "$", 2) == 0)
		return (DOLAR);
	else if (define_type_more(value, &type))
		return (type);
	else if (define_type_builtin(value, &type))
		return (type);
	return (WORD);
}
