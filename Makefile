CC=cc
CC_FLAGS=-Wall -Wextra -Werror
READLINE_FLAG=-lreadline
<<<<<<< HEAD
NAME=minishell.a
EXEC_NAME=minishell
INC_DIR=include
SRC_DIR=src
SRC_FILES=main.c
=======
NAME=minishell
INC_DIR=include
SRC_DIR=src
SRC_FILES=main.c parser_token_build.c parser_token_utils.c parser_token_define.c parser_token_char_utils.c parser_token_debug.c perform_token_lst.c 
>>>>>>> development
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

<<<<<<< HEAD
all: $(NAME) $(LIBFT)
	$(CC) $(CC_FLAGS) -o $(EXEC_NAME) $(NAME) $(LIBFT) $(READLINE_FLAG)
=======
all: $(OBJS) $(LIBFT)
	$(CC) $(CC_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_FLAG) -g
>>>>>>> development

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
