#!/bin/bash
#!/bin/bash
export LD_LIBRARY_PATH=./criterion-2.4.2/lib:$LD_LIBRARY_PATH
gcc -I \
	./criterion-2.4.2/include \
	minishell_test.c \
	../src/parser_token_build.c \
	../src/parser_token_utils.c \
	../src/parser_token_debug.c \
	../libft/libft.a \
	-L ./criterion-2.4.2/lib \
	-lcriterion \
	-o tests \
	&& ./tests --verbose
if [ $? -eq 0 ]; then
    echo "✅ All tests passed"
else
    echo "❌ Some tests failed"
fi
