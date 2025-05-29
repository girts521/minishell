NAME = minishell 
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c welcome.c ft_split.c check_command.c ft_strlen.c ft_strlcat.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
