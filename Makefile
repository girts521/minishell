NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Itokenizer -Ilibft -Ienviroment

LIBFT = libft/libft.a

SRCS = main.c \
	tokenizer/token.c tokenizer/token_utils.c tokenizer/free_token_list.c \
	enviroment/enviroment.c enviroment/env_utilis.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -rf $(OBJS)
	$(MAKE) -C libft clean

fclean : clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
