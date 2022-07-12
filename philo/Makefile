CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -Werror
CFLAGS		+=	-I $(INCLD)
CFLAGS		+=	-g

RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[1;33m
DEF			=	\033[0m

ifeq ($(PRETTY_PRINT), 1)
	CFLAGS += -D PRINT_STR="%-8zu %8zu %s\n"
endif

NAME 		=	philo
INCLD		=	include

SRC_DIR		=	src/
SRC 		=	main.c					\
				parse.c					\
				ft_atoi.c				\
				error_handler.c			\
				initialise.c			\
				simulation.c			\
				philosopher_actions.c	\
				monitoring.c			\
				time.c					\
				log_printer.c			\

P_SRC		=	$(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR		=	obj/
OBJ			=	$(SRC:.c=.o)
P_OBJ		=	$(addprefix $(OBJ_DIR), $(OBJ))

all:	$(NAME) $(NAME_B)

$(NAME):	$(P_OBJ) $(INCLD) 
	@$(CC) $(CFLAGS) $(P_OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled: $(shell pwd)$(DEF)"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo "compiling: $<"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)removed: $(OBJ_DIR)$(DEF)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)removed: $(NAME)$(DEF)"

re: fclean
	@make all

norm:
	norminette $(P_SRC)

run:
	@make all
	./$(NAME)

.PHONY:	all clean fclean re norm run