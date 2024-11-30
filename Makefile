#===================================================================================| Variables and paths

MAKEFLAGS += -s
NAME				= minishell
LIBFT				= ./ms_libft//libft.a
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/
CC					= cc
#------------|Lembrar de remover "-g" antes de submeter ("-g" for gdb)|
CFLAGS				= -Wall -Werror -Wextra -g -I$(INC)
#------------|Lembrar de remover "-g" antes de submeter ("-g" for gdb)|
RM					= rm -rf
SRCS				= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#===================================================================================| Colors |

RED = "\033[31m"
GREEN = "\033[32m"
ORANGE = "\033[38;5;208m"
PURPLE = "\e[35m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
RESET = "\033[0m"

#===================================================================================| Commands |

all: 				$(NAME)

$(NAME): 			$(OBJS) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
					@clear

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@
					@echo "🔧 Compiling... $<"

$(LIBFT):
					@make -C ./libft

clean:
					@$(RM) $(OBJ_DIR)/*
					@make clean -C ./libft

fclean: 			clean

re: 				fclean all

l:				re
				valgrind --leak-check=full --show-leak-kinds=all


#===================================================================================| Ignore |
#
#--| Any aditional note must be here !
#
#
#
#
#
#
#
#
#
#
#
#
#
#===================================================================================| Ignore |
