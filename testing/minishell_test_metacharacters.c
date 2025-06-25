#include "minishell_test.h"

TestSuite(minishell_test_suite_metacharacters, .init=init_test_redirect_stderr, .fini=clean_test);

Test(minishell_test_suite_metacharacters, test_metacharacters_1)
{
	char	*input = ">";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, ">");
	cr_assert_eq(ms->token_lst->type, REDIRECT_OUT);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_2)
{
	char	*input = "<";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "<");
	cr_assert_eq(ms->token_lst->type, REDIRECT_IN);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_3)
{
	char	*input = "|";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "|");
	cr_assert_eq(ms->token_lst->type, PIPE);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_4)
{
	char	*input = ">>";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, ">>");
	cr_assert_eq(ms->token_lst->type, APPEND);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_metacharacters_5)
{
	char	*input = "<<";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "<<");
	cr_assert_eq(ms->token_lst->type, HEREDOC);
	cr_assert_null(ms->token_lst->next);
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_1)
{
	char	*input = "echo > file";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "echo");
	cr_assert_str_eq(ms->token_lst->next->value, ">");
	cr_assert_str_eq(ms->token_lst->next->next->value, "file");
	cr_assert_eq(ms->token_lst->type, BUILTIN_ECHO);
	cr_assert_eq(ms->token_lst->next->type, REDIRECT_OUT);
	cr_assert_eq(ms->token_lst->next->next->type, WORD);
	unlink("file");
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_echo_1)
{
	char	*input = "echo>file";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "echo");
	cr_assert_str_eq(ms->token_lst->next->value, ">");
	cr_assert_str_eq(ms->token_lst->next->next->value, "file");
	cr_assert_eq(ms->token_lst->type, BUILTIN_ECHO);
	cr_assert_eq(ms->token_lst->next->type, REDIRECT_OUT);
	cr_assert_eq(ms->token_lst->next->next->type, WORD);
	unlink("file");
}

Test(minishell_test_suite_metacharacters, test_mix_metacharacters_echo_2)
{
	char	*input = "echo>>file";

	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "echo");
	cr_assert_str_eq(ms->token_lst->next->value, ">>");
	cr_assert_str_eq(ms->token_lst->next->next->value, "file");
	cr_assert_eq(ms->token_lst->type, BUILTIN_ECHO);
	cr_assert_eq(ms->token_lst->next->type, APPEND);
	cr_assert_eq(ms->token_lst->next->next->type, WORD);
	unlink("file");
}

Test(minishell_test_suite_metacharacters_stdout, test_mix_metacharacters_cat_1, .init=init_test_redirect_stdout_stderr, .fini=clean_test)
{
	char	*input = "cat << EOF > file";

	mock_input("Hello\nWorld\nEOF\n");
	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "cat");
	cr_assert_str_eq(ms->token_lst->next->value, "<<");
	cr_assert_str_eq(ms->token_lst->next->next->value, "EOF");
	cr_assert_str_eq(ms->token_lst->next->next->next->value, ">");
	cr_assert_str_eq(ms->token_lst->next->next->next->next->value, "file");
	cr_assert_eq(ms->token_lst->type, WORD);
	cr_assert_eq(ms->token_lst->next->type, HEREDOC);
	cr_assert_eq(ms->token_lst->next->next->type, WORD);
	cr_assert_eq(ms->token_lst->next->next->next->type, REDIRECT_OUT);
	cr_assert_eq(ms->token_lst->next->next->next->next->type, WORD);
	unlink("file");
}

Test(minishell_test_suite_metacharacters_stdout, test_mix_metacharacters_cat_2, .init=init_test_redirect_stdout_stderr, .fini=clean_test)
{
	char	*input = "cat<<EOF>file";

	mock_input("Hello\nWorld\nEOF\n");
	ms->input = input;
	res = token_lst_build(ms);
	cr_assert_eq(res, 1);
	usual_flow(ms);
	cr_assert_str_eq(ms->token_lst->value, "cat");
	cr_assert_str_eq(ms->token_lst->next->value, "<<");
	cr_assert_str_eq(ms->token_lst->next->next->value, "EOF");
	cr_assert_str_eq(ms->token_lst->next->next->next->value, ">");
	cr_assert_str_eq(ms->token_lst->next->next->next->next->value, "file");
	cr_assert_eq(ms->token_lst->type, WORD);
	cr_assert_eq(ms->token_lst->next->type, HEREDOC);
	cr_assert_eq(ms->token_lst->next->next->type, WORD);
	cr_assert_eq(ms->token_lst->next->next->next->type, REDIRECT_OUT);
	cr_assert_eq(ms->token_lst->next->next->next->next->type, WORD);
	unlink("file");
}
