CC 		=	gcc
CFLAGS 	=	-I $(INCLUDE) -Wall -Wextra -Werror -g

ifeq ($(PRETTY_PRINT), 1)
	CFLAGS += -D PRINT_STR="%-8zu %8zu %s\n"
endif

NAME 	=	philo

INCLUDE	=	include
SRC 	=	main.c					\
			parse.c					\
			ft_atoi.c				\
			error_handler.c			\
			initialise.c			\
			simulation.c			\
			philosopher_actions.c	\
			monitoring.c			\
			time.c					\
			log_printer.c			\

OBJ		= $(addprefix obj/, $(SRC:.c=.o))

RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[1;33m
DEF		=	\033[0m

all:	$(NAME)

$(NAME):	$(INCLUDE) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) is built$(DEF)"

obj/%.o:	src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

norm:
	norminette $(addprefix src/, $(SRC))

run:
	@make all
	./$(NAME)

.PHONY:	all clean fclean re norm run