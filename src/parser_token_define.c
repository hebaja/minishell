#include "../include/minishell.h"

int	define_type_builtin(char *value, t_token_type *type)
{
	int	res;

	res = 1;
	if (ft_strncmp(value, "echo", 5 ) == 0)
		*type = BUILTIN_ECHO;
	else if (ft_strncmp(value, "cd", 3) == 0)
		*type = BUILTIN_CD;
	else if (ft_strncmp(value, "pwd", 4) == 0)
		*type = BUILTIN_PWD;
	else if (ft_strncmp(value, "export", 8) == 0)
		*type = BUILTIN_EXPORT;
	else if (ft_strncmp(value, "unset", 5) == 0)
		*type = BUILTIN_UNSET;
	else if (ft_strncmp(value, "env", 4) == 0)
		*type = BUILTIN_ENV;
	else if (ft_strncmp(value, "exit", 5) == 0)
		*type = BUILTIN_EXIT;
	else 
		res = 0;
	return (res);
}

int	define_type_redirect(char *value, t_token_type *type)
{
	int	res;

	res = 1;
	if (ft_strncmp(value, ">", 2) == 0)
		*type = REDIRECT_OUT;
	else if (ft_strncmp(value, "<", 2) == 0)
		*type = REDIRECT_IN;
	else if (ft_strncmp(value, ">>", 3) == 0)
		*type = APPEND;
	else if (ft_strncmp(value, "<<", 3) == 0)
		*type = HEREDOC;
	else
		res = 0;

	return (res);
}

t_token_type	define_type(char *value)
{
	t_token_type type;

	if (ft_strncmp(value, "-", 1) == 0)
	{
		if (ft_strncmp(value + 1, " ", 1) != 0)
			return (FLAG);
	}
	else if (ft_strncmp(value, "|", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(value, "&", 2) == 0)
		return (BACKGROUND);
	else if (ft_strncmp(value, "&&", 3) == 0)
		return (AND);
	else if (ft_strncmp(value, "||", 3) == 0)
		return (OR);
	else if (ft_strncmp(value, "*", 3) == 0) /* NEEDS SPACE RIGHT BEFORE */
		return (WILDCARD);
	else if (ft_strncmp(value, "$", 3) == 0) /* NEEDS LETTER RIGHT AFTER */
		return (DOLAR);
	else if (define_type_redirect(value, &type))
		return (type);
	else if (define_type_builtin(value, &type))
		return (type);
	return (WORD);
}
