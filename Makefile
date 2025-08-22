NAME = minishell
CC = cc

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_INCLUDE = -I/opt/homebrew/opt/readline/include -I/usr/local/opt/readline/include
READLINE_LIB = -L/opt/homebrew/opt/readline/lib -L/usr/local/opt/readline/lib

CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR) -Itokenizer -Ienviroment -Iast_parser -Ibuilt-in $(READLINE_INCLUDE)
LDFLAGS = $(READLINE_LIB) -L$(LIBFT_DIR) -lft -lreadline

SRCS =	main.c ast_parser/ast_node_utils.c ast_parser/ast_utils.c ast_parser/parser_utils.c ast_parser/validate_tokens.c ast_parser/parser.c ast_parser/print_ast.c ast_parser/print_helpers.c \
		tokenizer/token.c tokenizer/token_utils.c tokenizer/free_token_list.c \
		enviroment/enviroment.c enviroment/env_utilis.c \
		execute_ast.c execute_utils.c \
		built-in/echo.c built-in/cd.c built-in/env.c built-in/exit.c built-in/export.c built-in/is_builtin.c built-in/pwd.c built-in/unset.c built-in/utils.c \
		redirection/handle_heredoc.c redirection/handle_redirs.c \
		utils_main.c ft_expantion.c helpers.c \
		signals.c
		# tests.c
OBJS := $(SRCS:.c=.o)

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
