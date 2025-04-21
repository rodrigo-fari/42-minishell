NAME= libft.a
CC= cc
FLAGS= -Wall -Wextra -Werror
RM= rm -rf
OBJ= $(SRC:.c=.o)
SRC= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memset.c ft_strlen.c ft_tolower.c ft_toupper.c ft_bzero.c \
	ft_strlcat.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	ft_strnstr.c ft_atoi.c ft_strdup.c ft_memcpy.c ft_memmove.c \
	ft_memchr.c ft_memcmp.c ft_calloc.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_itoa.c ft_strmapi.c ft_ptrhex.c ft_striteri.c ft_split.c \
	ft_lstnew_bonus.c ft_putnbr_fd.c ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
	ft_lstmap_bonus.c ft_printf.c ft_check_char.c ft_intncount.c \
	ft_putncount.c ft_int_len.c ft_strncount.c ft_unsint.c \
	ft_hexapplier.c ft_strcmp.c get_next_line.c get_next_line_utils.c \
	ft_str_chr_count.c ft_strnlen.c ft_matrix_finder.c free_splits.c \
	ft_strncpy.c ft_isspace.c ft_strcpy.c ft_strcat.c ft_realloc.c \
	ft_strndup.c ft_print_array.c ft_appen_char_to_string.c ft_atol.c \
	ft_atod.c

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ): $(SRC)
	@$(CC) $(FLAGS) -c $(SRC)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
