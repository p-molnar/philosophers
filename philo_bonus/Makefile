# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/12 11:28:33 by pmolnar       #+#    #+#                  #
#    Updated: 2022/09/06 11:18:55 by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# COMPILER CONFIG
CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -Werror
CFLAGS		+=	-g
CFLAGS		+=	-I $(INCLD)
INCLD		=	include

# PRINT FORMATTING
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[1;33m
BOLD			=	\033[1m
DEF				=	\033[0m
SPACE_W 		= 	%-40s
STATUS_W		=	%-12s
STATUS_FMT		=	$(BOLD)$(STATUS_W)$(DEF)$(SPACE_W)

# PRETTIER FORMATTING
ifeq ($(PRETTY_PRINT), 1)
	CFLAGS			+=	-D PRETTY_PRINT=1
	INFO_PP			=	"Pretty print on\n"
	PRETTY_PRINT	=	0
endif
#	ADDRESS SANITIZER 
ifeq ($(ADDRESS_SANIT), 1)
	CFLAGS			+=	-fsanitize=address
	INFO_AS			=	"Address sanitizer on\n"
	ADDRESS_SANIT	=	0
endif

# THREAD SANITIZER 
ifeq ($(THREAD_SANIT), 1)
	CFLAGS			+=	-fsanitize=thread
	INFO_TS			=	"Thread sanitizer on\n"
	THREAD_SANIT	=	0
endif

#	EXECUTABLE CONFIG
NAME 		=	philo_bonus
OUT_DIR		=	$(shell pwd)
P_OUT		=	$(addprefix $(OUT_DIR)/, $(NAME))

SRC_DIR		=	src/
SRC 		=	main.c					\
				parse.c					\
				error_handler.c			\
				time.c					\
				init.c					\
				process.c				\
				philo.c					\
				semaphore.c				\
				printer.c				\
				checker.c				\
				alloc.c					\
				string_util.c			\
				exit_checker.c			\


P_SRC		=	$(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR		=	obj/
OBJ			=	$(SRC:.c=.o)
P_OBJ		=	$(addprefix $(OBJ_DIR), $(OBJ))

# RECEPIES
all:	print_info $(NAME)
	@printf "$(GREEN)$(NAME) binary is compiled at $(OUT_DIR)$(DEF)\n"

$(NAME):	$(P_OBJ) $(INCLD)
	@printf "$(BOLD)%-52s$(DEF)" "compiling object file(s)"
	@$(CC) $(CFLAGS) $(P_OBJ) -o $(P_OUT)
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(STATUS_FMT)" "generating" "$@"
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

print_info:
	@printf "$(YELLOW)"$(INFO_PP)$(INFO_AS)$(INFO_TS)"$(DEF)"
	
.PHONY:	all clean fclean re norm print_info