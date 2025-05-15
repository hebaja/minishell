CC=cc
CC_FLAGS=-Wall -Wextra -Werror
READLINE_FLAG=-lreadline
NAME=minishell
INC_DIR=include
SRC_DIR=src
SRC_FILES=main.c parser_token_build.c parser_token_utils.c parser_token_define.c parser_token_char_utils.c parser_token_debug.c perform_token_lst.c builtins.c builtins_export.c extract_environment_variables.c builtin_unset.c
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

all: $(OBJS) $(LIBFT)
	$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_FLAG) -g

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

.PHONY: all clean fclean re
