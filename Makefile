#===================================================================================| Variables and paths |

MAKEFLAGS += -s
NAME				= minishell
LIBFT				= ./src/ms_libft/libft/libft.a
INC					= inc/
SRC_DIR				= src/
OBJ_DIR				= obj/
CC					= cc
SANITIZE_FALGS		= -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer
#------------|Lembrar de remover "-g" antes de submeter ("-g" gdb)|
CFLAGS				= -g3 -I$(INC)
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

all:				$(NAME)

$(NAME): 			$(OBJS) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@printf "🔧 Compiling %s %b[OK]%b\n" "$<" "$(GREEN)" "$(RESET)"
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
					@make -C ./src/ms_libft/libft/

clean:
					@$(RM) $(OBJ_DIR)
					@make clean -C ./src/ms_libft/libft/
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

val:				
					clear
						valgrind --leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes \
						--suppressions=readline_supressor ./$(NAME)

# Colors
GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

.PHONY: animate
animate:
	@# Frame 1 - HELL verde completo
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "                                                                                            "
	@echo " "
	@echo " "
	@sleep 1

	@# Frame 2 - HELL verde completo
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${GREEN}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${GREEN}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${GREEN}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${GREEN}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${GREEN}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${GREEN}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 3 - Primeira linha do HELL vermelha
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${GREEN}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${GREEN}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${GREEN}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${GREEN}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${GREEN}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 4 - Duas primeiras linhas do HELL vermelhas
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${GREEN}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${GREEN}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${GREEN}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${GREEN}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 5 - Três primeiras linhas do HELL vermelhas
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${RED}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${GREEN}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${GREEN}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${GREEN}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 6 - Quatro primeiras linhas do HELL vermelhas
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${RED}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${RED}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${GREEN}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${GREEN}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 7 - Cinco primeiras linhas do HELL vermelhas
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${RED}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${RED}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${RED}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${GREEN}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 8 - Seis primeiras linhas do HELL vermelhas
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${RED}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${RED}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${RED}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${RED}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${GREEN}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 9 - Sete primeiras linhas do HELL vermelhas
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${RED}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${RED}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${RED}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${RED}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${RED}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${GREEN}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	@sleep 0.2

	@# Frame 10 - HELL quase todo vermelho (exceto primeira linha)
	@clear
	@echo " "
	@echo " "
	@echo "${GREEN}       ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ${RED}██░ ██    ▓█████     ██▓        ██▓${RESET}"    
	@echo "${GREEN}     ▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ${RED}▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒${RESET}"    
	@echo "${GREEN}     ▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ${RED}▒██▀▀██░   ▒███      ▒██░       ▒██░${RESET}"    
	@echo "${GREEN}     ▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ${RED}░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░${RESET}"   
	@echo "${GREEN}     ▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ${RED}░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒${RESET}"
	@echo "${GREEN}     ░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ${RED}▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░${RESET}"
	@echo "${GREEN}     ░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ${RED}▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░${RESET}"
	@echo "${GREEN}     ░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ${RED}░  ░░ ░      ░        ░ ░        ░ ░${RESET}"   
	@echo "${GREEN}            ░       ░              ░     ░           ░      ${RED}░  ░  ░      ░  ░       ░  ░       ░  ░${RESET}"
	@echo "${GREEN}                                                                                            "
	@echo " "
	@echo " "
	./$(NAME)
#|=============================================================================|
#|
#|i hate shell ...
#|
#|=============================================================================|
