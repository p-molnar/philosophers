# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/14 22:59:51 by pmolnar       #+#    #+#                  #
#    Updated: 2022/07/14 23:10:26 by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# COMPILER CONFIG
CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -Werror
CFLAGS		+=	-I $(INCLD)
CFLAGS		+=	-g

# PRINT FORMATTING
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[1;33m
BOLD			=	\033[1m
DEF				=	\033[0m
SPACE_W 		= 	%-40s
STATUS_W		=	%-10s
STATUS_FMT		=	$(BOLD)$(STATUS_W)$(DEF) $(SPACE_W)

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
	@printf "$(STATUS_FMT)" "building" "$(NAME)"
	@$(CC) $(CFLAGS) $(P_OBJ) -o $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"
	@printf "$(GREEN)$(NAME) is created at $(shell pwd)$(DEF)\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(STATUS_FMT)" "compiling" "$<"
	@$(CC) $(CFLAGS) $^ -c -o $@
	@printf "[$(GREEN)DONE$(DEF)]\n"

clean:
	@printf "$(STATUS_FMT)" "removing" "$(OBJ_DIR)"
	@rm -rf $(OBJ_DIR)
	@printf "[$(GREEN)DONE$(DEF)]\n"

fclean: clean
	@printf "$(STATUS_FMT)" "removing" "$(NAME)"
	@rm -f $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"

re: fclean
	@make all

norm:
	norminette $(P_SRC)

run:
	@make all
	./$(NAME)

.PHONY:	all clean fclean re norm run