#!/bin/bash

export LD_LIBRARY_PATH=./criterion-2.4.2/lib:$LD_LIBRARY_PATH
gcc -I \
	./criterion-2.4.2/include \
	minishell_test.c \
	minishell_test_utils.c \
	minishell_test_builtin.c \
	minishell_test_quote.c \
	minishell_test_extra_meta.c \
	../src/parser_token_build.c \
	../src/parser_token_utils.c \
	../src/parser_token_define.c \
	../src/parser_token_char_utils.c \
	../src/parser_token_debug.c \
	../libft/libft.a \
	-L ./criterion-2.4.2/lib \
	-lcriterion \
	-o tests \
	&& ./tests --verbose
if [ $? -eq 0 ]; then
    echo "✅ All tests passed"
	exit 0
else
    echo "❌ Some tests failed"
	exit 1
fi
