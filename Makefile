CC 		=	gcc
CFLAGS 	=	-I $(INCLUDE) -Wall -Wextra -Werror
# CFLAGS 	=	-I $(INCLUDE) 

NAME 	=	philo

INCLUDE	=	include
SRC 	=	main.c		\
			input.c		\
			input_util.c\


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