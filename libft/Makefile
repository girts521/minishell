CC = cc
CFLAGS = -Werror -Wextra -Wall -Ibasic -Iprintf -Iget_next_line

NAME = libft.a
BASIC = basic/basic.a
PRINTF = printf/ft_printf.a
GETNEXTLINE = get_next_line/ft_getnextline.a

all: $(NAME)

$(BASIC):
	$(MAKE) -C basic

$(PRINTF):
	$(MAKE) -C printf

$(GETNEXTLINE):
	$(MAKE) -C get_next_line

$(NAME): $(BASIC) $(PRINTF) $(GETNEXTLINE)
	ar -x $(BASIC)
	ar -x $(PRINTF)
	ar -x $(GETNEXTLINE)
	ar rcs $(NAME) *.o
	rm -f *.o

clean:
	rm -f $(OBJS)
	$(MAKE) -C basic clean
	$(MAKE) -C printf clean
	$(MAKE) -C get_next_line clean

fclean:
	rm -f $(NAME)
	$(MAKE) -C basic fclean
	$(MAKE) -C printf fclean
	$(MAKE) -C get_next_line fclean

re:
	$(MAKE) fclean
	$(MAKE) all
