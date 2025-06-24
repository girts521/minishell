CC = cc
CFLAGS = -Werror -Wextra -Wall -Ibasic -Iprintf -Iget_next_line

NAME = libft.a
BASIC = basic/basic.a
PRINTF = printf/ft_printf.a
GETNEXTLINE = get_next_line/ft_getnextline.a

all: $(NAME)

$(BASIC):
	@printf "Compiling basic libft... "
	@{ \
		spin() { while :; do for x in / - \\ \|; do printf "\rCompiling basic libft... %s" "$$x"; sleep 0.1; done; done; }; \
		spin & \
		SPIN_PID=$$!; \
		$(MAKE) -C basic --silent; \
		kill $$SPIN_PID; \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\r\033[32m✅ Compiling basic libft... done\033[0m\n"; \
	}

$(PRINTF):
	@printf "Compiling printf... "
	@{ \
		spin() { while :; do for x in / - \\ \|; do printf "\rCompiling printf... %s" "$$x"; sleep 0.1; done; done; }; \
		spin & \
		SPIN_PID=$$!; \
		$(MAKE) -C printf --silent; \
		kill $$SPIN_PID; \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\r\033[32m✅ Compiling printf... done\033[0m\n"; \
	}

$(GETNEXTLINE): 
	@printf "Compiling get_next_line... "
	@{ \
		spin() { while :; do for x in / - \\ \|; do printf "\rCompiling get_next_line... %s" "$$x"; sleep 0.1; done; done; }; \
		spin & \
		SPIN_PID=$$!; \
		$(MAKE) -C get_next_line --silent; \
		kill $$SPIN_PID; \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\r\033[32m✅ Compiling get_next_line... done\033[0m\n"; \
	}

$(NAME): $(BASIC) $(PRINTF) $(GETNEXTLINE)
	@ar -x $(BASIC)
	@ar -x $(PRINTF)
	@ar -x $(GETNEXTLINE)
	@ar rcs $(NAME) *.o
	@rm -f *.o

clean:
	rm -f $(OBJS) 
	@$(MAKE) -C basic clean --silent
	@$(MAKE) -C printf clean --silent
	@$(MAKE) -C get_next_line clean --silent
	@printf "\r\033[32m✅ Cleaning done\033[0m\n"; \

fclean:
	rm -f $(NAME) 
	@$(MAKE) -C basic fclean --silent
	@$(MAKE) -C printf fclean --silent
	@$(MAKE) -C get_next_line fclean --silent
	@printf "\r\033[32m✅ Cleaning done\033[0m\n"; \

re:
	@$(MAKE) fclean --silent
	@$(MAKE) all --silent
