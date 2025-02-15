/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:19:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/15 18:31:49 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//=====================================| Colors |
# define RED "\001\033[1;31m\002"
# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;32m\002"
# define CYAN "\001\033[1;36m\002"
# define BLUE "\001\033[1;34m\002"
# define MAGENTA "\001\033[1;35m\002"
# define RESET "\001\033[0m\002"

//=====================================| Libraries |
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
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

//=====================================| Support Defines |
# define CLEAR_CODE	"\033[2J\033[H"
# define RESET		"\001\033[0m\002"

//=====================================| Structs |
typedef enum e_type
{
	TOKEN_WORD,// For commands and arguments
	TOKEN_PIPE,// For '|'
	TOKEN_REDIR_IN,// For '<'
	TOKEN_REDIR_OUT,// For '>'
	TOKEN_REDIR_APPEND,// For '>>'
	TOKEN_REDIR_HEREDOC,// For '<<'
	TOKEN_ENV_VAR,// For environment variables
}	t_type;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_ast_node
{
	t_type				*type;
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

//=====================================| ms_built-in |
//![bi_cd.c] - 5 functions limit achived.
void	bi_cd(char **args, t_env *env);
char	*find_oldpwd_in_env(t_env *env);
char	*find_path_home_in_env(t_env *env);
void	update_pwd(t_env *env, char *old_pwd);
bool	check_too_many_arguments(char **user_input);

//[bi_echo.c]
void	bi_echo(t_token *tmp);
bool	flag_verify(char *str);

//[bi_error.c]
void	bi_error(char *str);

//[bi_exec.c]
void	bi_exec(t_env *env, t_token *tokens, char **commands);
void	exec_exe(t_token *tmp, t_env *env, char **commands);

//[bi_exit.c]
int		is_numeric(const char *str);
void	handle_exit(t_token *tokens, t_env *env);
void	bi_exit(t_token *tokens, t_env *env, char **commands);

//[bi_export.c]
void	bi_export(t_env *env, char **user_input);
bool	env_add(t_env *env, char *key, char *value);

//[bi_pwd.c]
void	bi_pwd(void);

//[bi_unset.c]
void	env_remove(t_env *env, char *key);
void	bi_unset(char **user_input, t_env *env);

//=====================================| ms_env |
//[ev_env_manager.c]
t_env	*env_manager(t_env *env);

//[ev_env_to_struct.c]
t_env	*env_to_struct(char **environ);

//[ev_print_env.c]
void	print_env(t_env *env);

//![ev_utils.c] - 5 functions limit achived.
int		listsize(t_env *env);
t_env	*list_last(t_env *lst);
void	free_env_struct(t_env *env);
char	**array_envs(t_env *envs);
void	listadd_back(t_env **lst, t_env *new);

//=====================================| ms_main |
//[ms_exec.c]
void	ms_exec(char *input, t_env *env);

//[ms_free.c]
void	ms_free(t_env *env, char *input, char **commands, t_token *tokens);

//=====================================| ms_parsing |
//[ps_error.c]
void	ps_error(char *str);

//[ps_parsing.c]
bool	quote_verifier(char *input);
bool	ps_parsing(char **commands, int i);

//[ps_quotes.c]
bool	parse_quotes(char *input, int i, int validation);

//[ps_pipes.c]
bool	parse_pipes(char **commands);

//[ps_redins.c]
bool	parse_redin(char **commands);

//[ps_redout.c]
bool	parse_redout(char **commands);

//[ps_remove_quotes_1.c]
char	*extract_argument(char *input);
int		count_quotes(char *input, char quote);
int		has_only_one_kind_of_quote(char *input);
char	*extract_second_quote_and_argument(char *input, char first_quote);

//[ps_remove_quotes_2.c]
char	find_first_quote(char *str);
void	remove_quotes(char **commands);
int		count_first_quote(char *str, char quote);

//[ps_var_expand_1.c]
char	*env_compare(char *input);
char	*append_str(char *result, char *str);
char	*extract_variable(char *start, char **new_start);
char	*replace_variable(char *start, char **new_start);
char	*process_segment(char *result, char **start, char *end);

//[ps_var_expand_1.c]
char	*expand_variables(char *str);
void	replace_env_variables(char **commands);

//[ps_var_expand_utils.c]
char	*ft_charjoin(char *str, char c);
char	*ft_strjoin_free(char *s1, char *s2);

//=====================================| ms_sighand |
//[sh_sig_treatment.c]
void	sig_ctrl_c(int sig);

//=====================================| ms_tokenizer |
//[tk_print_tokens.c]
void	print_tokens(t_token *token);

//[tk_split.c]
char	*extract_word(char *input, int *i);
char	**tk_splitter(char *input, int i, int j);
int		tk_count_words(char *input, int i, int count);

//[tk_tokenizer.c]
int		token_type(char *token);
t_token	*token_to_struct(char **commands);

//![tk_utils.c] - 5 functions limit achived.
int		tk_listsize(t_token *token);
t_token	*tk_list_last(t_token *lst);
void	free_token_struct(t_token *token);
int		skip_whitespace(char *input, int i);
void	tk_listadd_back(t_token **lst, t_token *new);

//=====================================| Endif |
#endif
