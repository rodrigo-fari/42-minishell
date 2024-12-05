/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:19:21 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/05 18:40:14 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//=====================================| Colors |
# define RED    "\033[31m"
# define GREEN  "\033[32m"
# define ORANGE "\033[38;5;208m"
# define PURPLE "\e[35m"
# define YELLOW "\033[33m"
# define CYAN   "\033[36m"
# define RESET  "\033[0m"

//=====================================| Libraries |
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include "../src/ms_libft/libft/libft.h"

//#include "../../inc/minishell.h"
//Para a criacao dos arquivos

//=====================================| Support Defines |

//=====================================| Structs |
typedef struct s_struct
{
	void		*any_data;
}				t_struct;

typedef enum e_token_type
{
	TOKEN_WORD,// For commands and arguments
	TOKEN_PIPE,// For '|'
	TOKEN_REDIR_IN,// For '<'
	TOKEN_REDIR_OUT,// For '>'
	TOKEN_REDIR_APPEND,// For '>>'
	TOKEN_REDIR_HEREDOC,// For '<<'
	TOKEN_ENV_VAR,// For environment variables
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				value;
	struct s_token		*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		*type;
	char				args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

//=====================================| ms_env.c |
t_env	*env_to_struct(char **environ);

//=====================================| ms_utils.c |
t_env	*list_last(t_env *lst);
void	print_env(t_env *head);
void	listadd_back(t_env **lst, t_env *new);

//=====================================| ms_utils.c |
void	validator(int validator, char *str);

//=====================================| ps_parsing.c |
void	parsing(char *input);

//=====================================| ps_syntax.c |
bool	parse_pipes(char **user_input);
bool	quote_check(char *input, int i, int s_quote, int d_quote);

//=====================================| ps_errors.c |
void	error_hand(char *str);

//=====================================| Endif |
#endif