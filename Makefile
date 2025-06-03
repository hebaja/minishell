CC=cc
CC_FLAGS=-Wall -Wextra -Werror -g
READLINE_FLAG=-lreadline
NAME=minishell
INC_DIR=include
SRC_DIR=src
SRC_FILES=main.c parser_token_build.c parser_token_char_utils.c parser_analyse.c parser_modes.c \
		token_define.c token_utils.c token_clear.c var_expansion.c var_quotes_expansion.c \
		var_expansion_utils.c quote_removal.c token_joining.c parser_conclusion.c builtin_exit.c \
		builtin_unset.c builtin_export.c builtin_cd.c builtins_common.c env_build.c env_utils.c \
		env_print_sort.c parser_token_debug.c
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)
TEST_DIR=testing

all: $(OBJS) $(LIBFT)
	$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_FLAG)

$(LIBFT):
	make -C $(LIBFT_DIR)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS) $(MINILIBX)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(EXEC_NAME)

re: fclean all

test: $(LIBFT)
	@cd $(TEST_DIR) && ./run_test.sh

.PHONY: all clean fclean re
