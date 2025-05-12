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

int	is_join(char **abs_value)
{
	if (*(*abs_value - 1)
		&& (*(*abs_value - 1) == '\''
		|| *(*abs_value - 1) == '\"'))
		return (1);
	return (0);
}

void	set_extra_meta_chars(t_token *token, char *value_start, char quote)
{
	if (is_dolar(value_start) && quote == 0)
		token->type = VAR;
	if (token->type == WILDCARD_SOLO && *++value_start != '\0')
	{
		if (*value_start != ' ')
			token->type = WILDCARD_JOIN;
	}
}

int	define_type_builtin(char *value, t_token_type *type)
{
	int	res;

	res = 1;
	if (ft_strncmp(value, "echo", 5) == 0)
		*type = BUILTIN_ECHO;
	else if (ft_strncmp(value, "cd", 2) == 0)
		*type = BUILTIN_CD;
	else if (ft_strncmp(value, "pwd", 3) == 0)
		*type = BUILTIN_PWD;
	else if (ft_strncmp(value, "export", 7) == 0)
		*type = BUILTIN_EXPORT;
	else if (ft_strncmp(value, "unset", 6) == 0)
		*type = BUILTIN_UNSET;
	else if (ft_strncmp(value, "env", 3) == 0)
		*type = BUILTIN_ENV;
	else if (ft_strncmp(value, "exit", 4) == 0)
		*type = BUILTIN_EXIT;
	else
		res = 0;
	return (res);
}

int	define_type_more(char *value, t_token_type *type, char c)
{
	int	res;

	res = 1;
	if (c == '\'')
		*type = SINGLE_QUOTED;
	else if (c == '\"')
		*type = DOUBLE_QUOTED;
	else if (ft_strncmp(value, ">>", 2) == 0)
		*type = APPEND;
	else if (ft_strncmp(value, "<<", 2) == 0)
		*type = HEREDOC;
	else if (ft_strncmp(value, ">", 1) == 0)
		*type = REDIRECT_OUT;
	else if (ft_strncmp(value, "<", 1) == 0)
		*type = REDIRECT_IN;
	else
		res = 0;
	return (res);
}

t_token_type	define_type(char *value, char c, int is_word_join)
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
		return (WILDCARD_SOLO);
	else if (define_type_more(value, &type, c))
		return (type);
	else if (define_type_builtin(value, &type))
		return (type);
	else if (is_word_join)
		return (WORD_JOIN);
	return (WORD);
}
