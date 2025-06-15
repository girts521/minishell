NAME = minishell
CC = cc
SRCS = main.c ast_parser/ast_node_utils.c ast_parser/ast_utils.c ast_parser/parser_utils.c ast_parser/validate_tokens.c ast_parser/parser.c ast_parser/print_ast.c ast_parser/print_helpers.c tokenizer/token.c tokenizer/token_utils.c tokenizer/free_token_list.c enviroment/enviroment.c enviroment/env_utilis.c

OBJS := $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR) -Itokenizer -Ienviroment -Iast_parser 
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re


