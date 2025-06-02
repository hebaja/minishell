#include "minishell_test.h"

TestSuite(minishell_test_suite_metacharacters, .init=redirect_stdout_err);

Test(minishell_test_suite_metacharacters, test_metacharacters_1)
{
	t_env	*env_lst;
	char	*input = ">";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, ">");
	cr_assert_eq(token_lst->type, REDIRECT_OUT);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_2, .init = redirect_stdout_err)
{
	t_env	*env_lst;
	char	*input = "<";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "<");
	cr_assert_eq(token_lst->type, REDIRECT_IN);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_3, .init = redirect_stdout_err)
{
	t_env	*env_lst;
	char	*input = "|";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "|");
	cr_assert_eq(token_lst->type, PIPE);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_4, .init = redirect_stdout_err)
{
	t_env	*env_lst;
	char	*input = ">>";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, ">>");
	cr_assert_eq(token_lst->type, APPEND);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_5, .init = redirect_stdout_err)
{
	t_env	*env_lst;
	char	*input = "<<";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "<<");
	cr_assert_eq(token_lst->type, HEREDOC);
	cr_assert_null(token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_1)
{
	t_env	*env_lst;
	char	*input = "echo > file";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "echo");
	cr_assert_str_eq(token_lst->next->value, ">");
	cr_assert_str_eq(token_lst->next->next->value, "file");
	cr_assert_eq(token_lst->type, BUILTIN_ECHO);
	cr_assert_eq(token_lst->next->type, REDIRECT_OUT);
	cr_assert_eq(token_lst->next->next->type, WORD);
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_echo_1)
{
	t_env	*env_lst;
	char	*input = "echo>file";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "echo");
	cr_assert_str_eq(token_lst->next->value, ">");
	cr_assert_str_eq(token_lst->next->next->value, "file");
	cr_assert_eq(token_lst->type, BUILTIN_ECHO);
	cr_assert_eq(token_lst->next->type, REDIRECT_OUT);
	cr_assert_eq(token_lst->next->next->type, WORD);
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_echo_2)
{
	t_env	*env_lst;
	char	*input = "echo>>file";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "echo");
	cr_assert_str_eq(token_lst->next->value, ">>");
	cr_assert_str_eq(token_lst->next->next->value, "file");
	cr_assert_eq(token_lst->type, BUILTIN_ECHO);
	cr_assert_eq(token_lst->next->type, APPEND);
	cr_assert_eq(token_lst->next->next->type, WORD);
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_cat_1)
{
	t_env	*env_lst;
	char	*input = "cat << EOF > file";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "cat");
	cr_assert_str_eq(token_lst->next->value, "<<");
	cr_assert_str_eq(token_lst->next->next->value, "EOF");
	cr_assert_str_eq(token_lst->next->next->next->value, ">");
	cr_assert_str_eq(token_lst->next->next->next->next->value, "file");
	cr_assert_eq(token_lst->type, WORD);
	cr_assert_eq(token_lst->next->type, HEREDOC);
	cr_assert_eq(token_lst->next->next->type, WORD);
	cr_assert_eq(token_lst->next->next->next->type, REDIRECT_OUT);
	cr_assert_eq(token_lst->next->next->next->next->type, WORD);
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_cat_2)
{
	t_env	*env_lst;
	char	*input = "cat<<EOF>file";

	env_lst = build_envp();
	res = token_lst_build(&token_lst, input);
	cr_assert_eq(res, 1);
	usual_flow(&token_lst, env_lst);
	cr_assert_str_eq(token_lst->value, "cat");
	cr_assert_str_eq(token_lst->next->value, "<<");
	cr_assert_str_eq(token_lst->next->next->value, "EOF");
	cr_assert_str_eq(token_lst->next->next->next->value, ">");
	cr_assert_str_eq(token_lst->next->next->next->next->value, "file");
	cr_assert_eq(token_lst->type, WORD);
	cr_assert_eq(token_lst->next->type, HEREDOC);
	cr_assert_eq(token_lst->next->next->type, WORD);
	cr_assert_eq(token_lst->next->next->next->type, REDIRECT_OUT);
	cr_assert_eq(token_lst->next->next->next->next->type, WORD);
}
