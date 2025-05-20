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
	if (type == WILDCARD_SOLO)
		return ("WILDCARD_SOLO");
	if (type == WILDCARD_JOIN)
		return ("WILDCARD_JOIN");
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

void	clean_values(char **values)
{
	while(*values)
	{
		free(*values);
		values++;
	}
	values = NULL;
}

char	**populate_values(int size, ...)
{
	int		i;
	char	**strs;
	va_list	args;

	i = -1;
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	va_start(args, size);
	while (++i < size)
		strs[i] = ft_strdup(va_arg(args, char *));
	va_end(args);
	strs[i] = NULL;
	return (strs);
}

char	**split_token_lst(t_token *token_lst)
{
	char	**split_values;
	size_t	size;
	int		i;

	size = token_lst_size(token_lst);
	split_values = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (token_lst)
	{
		split_values[i] = ft_strdup(token_lst->value);
		token_lst = token_lst->next;
		i++;
	}
	split_values[i] = NULL;
	return split_values;
}

char	**fetch_tokens_type_list(t_token *token_lst)
{
	char	**tokens_type_list;
	char	*type_str;

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
	char	*unquoted;

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

void	test_lst(t_token *token_lst, char **values, char **types)
{
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	cr_assert_null(token_lst);
	token_lst_clear(&token_lst);
}

void	usual_flow(t_token **token_lst)
{
	var_expansion(token_lst);
	quotes_var_expansion(token_lst);
	quote_removal(*token_lst);
	token_joining(token_lst);
	conclude_parser(*token_lst);
}
