#===================================================================================| Variables and paths

MAKEFLAGS += -s
NAME				= minishell
LIBFT				= ./src/ms_libft/libft/libft.a
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/
CC					= cc
#------------|Lembrar de remover "-g" antes de submeter ("-g" gdb)|
CFLAGS				= -Wall -Werror -Wextra -g -I$(INC)
#---------------------------------------------------------------------|
RM					= rm -rf
SRCS				= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#===================================================================================| Colors |

RED = "\033[31m"
GREEN = "\033[32m"
ORANGE = "\033[38;5;208m"
PURPLE = "\033[35m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
RESET = "\033[0m"

#===================================================================================| Commands |

all: 				$(NAME)

$(NAME): 			$(OBJS) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
					@clear
					@echo " "
					@echo " "
					@echo $(GREEN)"   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       "
					@echo " ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       "
					@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       "
					@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       "
					@echo " ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       "
					@echo " ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       "
					@echo " ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ "
					@echo "  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ "
					@echo "                                                                                                  " $(RESET)
					@echo " "
					@echo " "
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@clear
					@echo "🔧 Compiling..."
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@
#					@echo "🔧 Compiling... $<"

$(LIBFT):
					@make -C ./src/ms_libft/libft/

clean:
					@$(RM) $(OBJ_DIR)
					@make clean -C ./src/ms_libft/libft/
					@$(RM) $(NAME)
					@clear
					@echo " "
					@echo " "
					@echo "🗑️ - Program has been cleaned!"
					@echo " "
					@echo " "
					@sleep 1
					@clear

fclean: 			clean

re: 				fclean all

n:
					norminette -R CheckForbiddenSourceHeader

l:					all
					valgrind --leak-check=full --show-leak-kinds=all \
						--suppressions=readline_leaks ./$(NAME)

lmac:
					leaks --atExit --list -- ./$(NAME)



#===================================================================================| Ignore |
#
# Any aditional note must be here !
#
#
# env_to_array
# handle dos sinais
# tratar $
# tratar do exit
# tratar $?
# 
#
#
#
#
#
#
#
#===================================================================================| Ignore |
