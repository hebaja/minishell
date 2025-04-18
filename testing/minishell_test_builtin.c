#include "minishell_test.h"

Test(minishell_test_suite, build_token_lst_test_all_builtins)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "echo cd pwd export unset env exit";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}
 
Test(minishell_test_suite, build_token_lst_test_builtin_echo)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "echo -n Hello";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);

	// print_tokens(token_lst);
	// i = -1;
	// while (++i < 4)
	// {
	// 	ft_printf("%d - ", i);
	// 	ft_printf("%s\n", types[i]);
	// }

	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_test_builting_cd)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "cd /home/user/folder";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_pwd)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "pwd";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_export)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "export VARIABLE=VALUE";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_unset)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "unset VARIABLE";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_env)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "env";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_exit)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "exit";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_mixed)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "echo >> doc || cat --abord < ls -l";
	char		**values = ft_split(input, ' ');
	char		**types;

	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}

Test(minishell_test_suite, build_token_lst_builtin_mixed_2)
{
	int		i;
	int		res;
	t_token	*token_lst;
	char	*input = "echo>>doc || less<more";
	char	**values = malloc(sizeof(char *) * 8);
	char	**types = malloc(sizeof(char *) * 8);

	values[0] = ft_strdup("echo");
	values[1] = ft_strdup(">>");
	values[2] = ft_strdup("doc");
	values[3] = ft_strdup("||");
	values[4] = ft_strdup("less");
	values[5] = ft_strdup("<");
	values[6] = ft_strdup("more");
	values[7] = NULL;
	token_lst = NULL;
	res = token_lst_build(&token_lst, input);
	types = fetch_tokens_type_list(token_lst);
	cr_assert_eq(res, 1);
	i = 0;
	while (token_lst)
	{
		test_token_lst(token_lst, values[i], types[i]);
		token_lst = token_lst->next;
		i++;
	}
	token_lst_clear(&token_lst);
}
