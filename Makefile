CC 		=	gcc
CFLAGS 	=	-I $(INCLUDE) -Wall -Wextra -Werror -fsanitize=address -g 
# CFLAGS 	=	-I $(INCLUDE) 

NAME 	=	philo

INCLUDE	=	include
SRC 	=	main.c				\
			parse.c				\
			ft_atoi.c			\
			error_handler.c		\
			initialise.c		\
			simulation.c		\
			philosopher.c		\
			philosopher_util.c	\
			die_checker.c		\

OBJ		= $(addprefix obj/, $(SRC:.c=.o))

all:	$(NAME)

$(NAME):	$(INCLUDE) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) is built"

obj/%.o:	src/%.c
	mkdir -p obj
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