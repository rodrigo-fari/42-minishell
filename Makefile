#===================================================================================| Variables and paths |

MAKEFLAGS += -s
NAME				= minishell
LIBFT				= ./src/ms_libft/libft/libft.a
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/
CC					= cc
#------------|Lembrar de remover "-g" antes de submeter ("-g" gdb)|
CFLAGS				= -Wall -Werror -Wextra -I$(INC)
#---------------------------------------------------------------------|
RM					= rm -rf
SRCS				= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#===================================================================================| Colors |

RED					= "\033[31m"
GREEN				= "\033[32m"
ORANGE				= "\033[38;5;208m"
PURPLE				= "\033[35m"
YELLOW				= "\033[33m"
CYAN				= "\033[36m"
RESET				= "\033[0m"

#===================================================================================| Commands |

all: 				$(NAME)
					@clear
					@echo " "
					@echo " "
					@echo " ✅ Minishell has compiled successfully!"
					@echo " "
					@echo " "
					./$(NAME)

$(NAME): 			$(OBJS) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@clear
					@echo "🔧 Compiling..."
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@


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
					@$(RM) $(NAME)

re: 				fclean all

norm:
					norminette -R CheckForbiddenSourceHeader

val:			all
					valgrind --leak-check=full --show-leak-kinds=all \
						--suppressions=readline_leaks ./$(NAME)

leaks:
					leaks --atExit --list -- ./$(NAME)

#===================================================================================| Notes |
#
# Any additional notes or tasks can be added here.
#
#===================================================================================| End |