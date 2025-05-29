CC = cc
CFLAGS = -Werror -Wextra -Wall

NAME = ft_printf.a

SRCS =	ft_printf.c ft_printf_c.c ft_printf_d_i.c ft_printf_p.c \
	ft_printf_s.c ft_printf_u.c ft_printf_x.c ft_printf_xx.c
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
