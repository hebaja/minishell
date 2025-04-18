#include "minishell_test.h"

void redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

char    *fetch_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == BACKGROUND)
		return ("BACKGROUND");
	if (type == WILDCARD)
		return ("WILDCARD");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == DOLAR)
		return ("DOLAR");
	if (type == BUILTIN_ECHO)
		return ("BUILTIN_ECHO");
	if (type == BUILTIN_CD)
		return ("BUILTIN_CD");
	if (type == BUILTIN_ENV)
		return ("BUILTIN_ENV");
	if (type == BUILTIN_PWD)
		return ("BUILTIN_PWD");
	if (type == BUILTIN_EXIT)
		return ("BUILTIN_EXIT");
	if (type == BUILTIN_UNSET)
		return ("BUILTIN_UNSET");
	if (type == BUILTIN_EXPORT)
		return ("BUILTIN_EXPORT");
	if (type == SINGLE_QUOTED)
		return ("SINGLE_QUOTED");
	if (type == DOUBLE_QUOTED)
		return ("DOUBLE_QUOTED");
	return ("");
}

char	**fetch_tokens_type_list(t_token *token_lst)
{
	char	**tokens_type_list;
	char	*type_str;
	size_t	size;
	int		i;

	tokens_type_list = (char **)malloc(sizeof(char *) * (token_lst_size(token_lst) + 1));
	i = 0;
	while (token_lst)
	{
		size = 0;
		type_str = fetch_token_type(token_lst->type);
		size = ft_strlen(type_str);
		tokens_type_list[i] = strdup(type_str);
		token_lst = token_lst->next;
		i++;
	}
	return (tokens_type_list);
}

void	unquoted_value_test(t_token *token_lst, char *value, char quote)
{
	int		i;
	char	*unquoted;
	size_t	size;

	i = -1;
	size = 0;
	value++;
	while (value[size] != quote && value[size])
		size++;
	size++;
	unquoted = (char *)malloc(sizeof(char) * (size));
	ft_strlcpy(unquoted, value, size);
	cr_assert_str_eq(token_lst->value, unquoted);
}

void	test_token_lst(t_token *token_lst, char *value, char *type)
{
	if (*value == '\'' || *value == '\"')
		unquoted_value_test(token_lst, value, *value);
	else
		cr_assert_str_eq(token_lst->value, value);
	cr_assert_str_eq(fetch_token_type(token_lst->type), type);
}
