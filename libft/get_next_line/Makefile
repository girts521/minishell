CC = cc
CFLAGS = -Werror -Wextra -Wall

NAME = ft_getnextline.a

SRCS = get_next_line_utils.c get_next_line.c
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
