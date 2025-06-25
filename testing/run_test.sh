#!/bin/bash

export LD_LIBRARY_PATH=./criterion-2.4.2/lib:$LD_LIBRARY_PATH
gcc -I \
	./criterion-2.4.2/include \
	minishell_test_utils.c \
	minishell_test_globals.c \
	minishell_test_builtin.c \
	minishell_test_builtin_cd.c \
	minishell_test_builtin_echo.c \
	minishell_test_builtin_exit.c \
	minishell_test_builtin_export.c \
	minishell_test_builtin_unset.c \
	minishell_test.c \
	minishell_test_cmd.c \
	minishell_test_exec_pipe.c \
	minishell_test_extra_meta.c \
	minishell_test_metacharacters.c \
	minishell_test_quote.c \
	minishell_test_quote_removal.c \
	minishell_test_redirect.c \
	minishell_test_token_join.c \
	minishell_test_var.c \
	minishell_test_var_quote.c \
	../src/parser_token_build.c \
	../src/parser_token_char_utils.c \
	../src/parser_modes.c \
	../src/var_expansion.c \
	../src/var_quotes_expansion.c \
	../src/var_expansion_utils.c \
	../src/env_build.c \
	../src/env_utils.c \
	../src/env_print.c \
	../src/quote_removal.c \
	../src/token_define.c \
	../src/token_joining.c \
	../src/token_utils.c \
	../src/token_clear.c \
	../src/parser_conclusion.c \
	../src/builtins_common.c \
	../src/builtin_cd.c \
	../src/builtin_export.c \
	../src/builtin_unset.c \
	../src/builtin_exit.c \
	../src/builtin_echo.c \
	../src/clean_utils.c \
	../src/cmd_build.c \
	../src/cmd_utils.c \
	../src/cmd_rebuild.c \
	../src/cmd_build_utils.c \
	../src/cmd_env_utils.c \
	../src/cmd_exec.c \
	../src/cmd_exec_utils.c \
	../src/iterate_utils.c \
	../src/signal_utils.c \
	../src/redirect.c \
	../src/redirect_utils.c \
	../src/pid_wait.c \
	../src/expand_status.c \
	../src/parser_token_debug.c \
	../libft/libft.a \
	-L ./criterion-2.4.2/lib \
	-lcriterion \
	-o tests -lreadline

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed"
    exit 1
fi

# Run with valgrind to check for memory leaks
# valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./tests
./tests

if [ $? -eq 0 ]; then
    echo "✅ All tests passed"
	exit 0
else
    echo "❌ Some tests failed"
	exit 1
fi
