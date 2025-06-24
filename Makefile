NAME = minishell
CC = cc
SRCS = main.c lexer.c print_ast.c ast_node_utils.c ast_utils.c parser_utils.c validate_tokens.c parser.c tokenizer/token.c tokenizer/token_utils.c tokenizer/free_token_list.c enviroment/enviroment.c enviroment/env_utilis.c

CFLAGS = -Wall -Wextra -Werror
OBJS := $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR) -I./ -Itokenizer -Ilibft -Ienviroment

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

fclean : clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
