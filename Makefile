CC=cc
CC_FLAGS=-Wall -Wextra -Werror
READLINE_FLAG=-lreadline
NAME=minishell.a
EXEC_NAME=minishell
INC_DIR=include
SRC_DIR=src
SRC_FILES=main.c
LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

all: $(NAME) $(LIBFT)
	$(CC) $(CC_FLAGS) -o $(EXEC_NAME) $(NAME) $(LIBFT) $(READLINE_FLAG) -g

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $@ $(OBJS) $(LIBFT)

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
