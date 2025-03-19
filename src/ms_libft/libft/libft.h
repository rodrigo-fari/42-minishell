/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:41:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/19 14:08:23 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//---------Libft Library----------//
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>

//---------Gnl Buffer----------//
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

//---------Printf Library----------//
# include <stdarg.h>

//---------Gnl Library----------//
# include <fcntl.h>

//---------Libft Functions---------//
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isspace(int c);
int		free_splits(char **line);
int		ft_atoi(const char *nptr);
int		ft_strnlen(char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_matrix_finder(char *str, int c);
int		ft_str_chr_count(char *str, int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strncpy(char *dst, const char *src, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);

void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_print_array(char **array);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t new_size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

//---------Libft Bonus Functions---------//
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));

//---------ft_printf Functions---------//

int		ft_int_len(int num);
int		ft_printf(const char *format, ...);

void	ft_putnbr_fd(int n, int fd);
void	ft_putncount(char a, int *total);
void	ft_strncount(char *string, int *total);
void	ft_unsint(unsigned int num, int *total);
void	ft_intncount(va_list ap, char format, int *total);
void	ft_ptrhex(char format, unsigned long num, int *total);
void	ft_hexapplier(char format, unsigned long num, int *total);
void	ft_check_char(const char *format, va_list ap, int *total);

//---------Get Next Line Functions---------//

char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *str);
char	*ft_update_data(char *s_buffer);
char	*ft_extract_line(char *s_buffer);
int		ft_check_character(char *str, int c);
char	*ft_strjoin_gnl(char *str1, char *str2);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*ft_read_from_file(char *s_buffer, int fd);
char	*ft_strcpy_nl(char *src, char *dest, int nl_stop);

//---------End If---------//
#endif
