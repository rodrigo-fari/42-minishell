/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:19:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/06 20:51:11 by aeberius         ###   ########.fr       */
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
# include <stddef.h>
# include "../src/ms_libft/libft/libft.h"

//=====================================| Support Defines |
# define LONG_MAX 9223372036854775807
# define LONG_MIN -9223372036854775808

//=====================================| Global Variable |
extern int	g_exit_status;

//=====================================| Structs |
typedef enum e_type
{
	TOKEN_WORD,				// For commands and arguments
	TOKEN_PIPE,				// For '|'
	TOKEN_REDIR_IN,			// For '<'
	TOKEN_REDIR_OUT,		// For '>'
	TOKEN_REDIR_OUT_APPEND,// For '>>'
	TOKEN_REDIR_ERR,		// For '2>'
	TOKEN_REDIR_ERR_APPEND,// For '2>>'
	TOKEN_ENV_VAR,			// For environment variables
	TOKEN_CMD,				// For command
	TOKEN_FILENAME,			// For filename
	TOKEN_HEREDOC			// For heredoc
}	t_type;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_ast_node
{
	t_type				type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	bool				has_equal;
	struct s_env		*next;
}	t_env;

//=========================================================================================

void		free_ast(t_ast_node *node);
t_ast_node	*create_node(t_type type);
t_ast_node	*build_ast(t_token *tokens);
void		handle_redir(t_ast_node **root, t_token **token);
void		handle_pipe(t_ast_node **root, t_ast_node *new_node, t_token **token);
void		execute_ast(t_ast_node *node, t_env *env);
void		execute_forked_cmd(t_ast_node *node, t_env *env);
void		handle_command(t_ast_node **root, t_ast_node **current, t_token **token);
void		pipe_child1(int *pipefd, t_ast_node *left, t_env *env);
void		pipe_child2(int *pipefd, t_ast_node *right, t_env *env);
void		execute_pipe(t_ast_node *left, t_ast_node *right, t_env *env);
int			get_redir_fd(t_ast_node *node, char *filename);
void		execute_redirection(t_ast_node *node, t_env *env);
int			is_redir(t_type type);
void		handle_redir_fd(t_ast_node *node, int fd);
int			is_builtin(char *cmd);





int			execute_heredoc(t_ast_node *node);
void		handle_heredoc_input(const char *delimiter, int fd);
int			execute_heredoc(t_ast_node *node);
void		handle_heredoc(t_ast_node **root, t_token **token);
void		env_remove(t_env *env, char *key);





char		**array_envs(t_env *envs);


void		ps_error(char *str);
char		*var_expand(char *input);
bool		quote_verifier(char *input);
bool		ps_parsing(char **commands, int i);
bool		parse_quotes(char *input, int i, int validation);
bool		parse_pipes(char **commands);
bool		parse_redin(char **commands);
bool		parse_redout(char **commands);
void		quote_fix(t_token *tokens);
char		*verify_quotes(char *input);
char		*replace_values(char *input, char current_quote, bool key, t_env *env);
char		*remove_quotes_and_expand(char *input, t_env *env);
char		*remove_quotes(char *input);
bool		bool_changer(bool key);
char		*extract_var_name(char *input, int *i);
char		*get_env_value(t_env *env, char *var_name);
char		*append_string_to_string(char *str1, const char *str2);
void		sig_ctrl_c(int sig);
void		print_tokens(t_token *token);
int			is_special_char(char c);
char		*extract_word(char *input, int *i);
char		**tk_splitter(char *input, int i, int j);
int			tk_count_words(char *input, int i, int count);
int			token_type(char *token);
t_token		*token_to_struct(char **commands);
int			tk_listsize(t_token *token);
void		free_token_struct(t_token *token);
int			skip_whitespace(char *input, int i);
void		tk_listadd_back(t_token **lst, t_token *new);
t_ast_node	*build_ast(t_token *tokens);
void		free_ast(t_ast_node *node);
void		execute_redirection(t_ast_node *node, t_env *env);
void		execute_ast(t_ast_node *node, t_env *env);


//================================ |ms_built-ins| =====================================================//

//bi_cd.c - 5 functions //
char	*find_oldpwd_in_env(t_env *env);
char	*find_path_home_in_env(t_env *env);
void	bi_cd(char **user_input, t_env *env);
void	update_pwd(t_env *env, char *old_pwd);
bool	check_too_many_arguments(char **user_input);

//bi_cd_2.c - 2 functions //
void	handle_cd_error(void);
void	change_directory(const char *path, t_env *env, char *old_pwd);

//bi_echo.c - 2 functions //
void	bi_echo(t_token *tmp);
bool	flag_verify(char *str);

//bi_error.c - 1 function //
void	bi_error(char *str);

//bi_exec.c - 5 functions //
void	handle_builtin_or_empty(char **commands, t_env *env);
char	*find_executable(char **paths, const char *cmd);
char	*resolve_command_path(const char *cmd, t_env *env);
char	*check_direct_path(const char *cmd);
void	handle_command_not_found(char *command);

//bi_exec_2.c - 4 functions //
void	bi_exec(char **commands, t_env *env);
void	handle_directory_error(char *command);
void	execute_builtin(char **commands, t_env *env);
void	check_command_path(char *command_path, char **commands);

//bi_exit.c - 5 functions //
void	bi_exit(t_token *token);
bool	check_signal_quantity(int qnt);
bool	check_exit_signals(t_token *token);
bool	check_exit_arguments(t_token *token);
void	define_exit_status(char *exit_status);

//bi_export.c - 5 functions //
bool	is_valid_key(char *key);
void	bi_export(t_env *env, char **user_input);
void	env_add(t_env *env, char *key, char *value, bool has_equal);
void	process_key_value(t_env *env, char *key, char *value, bool has_equal);
void	process_key_value(t_env *env, char *key, char *value, bool has_equal);

//bi_export_2.c - 3 functions //
void	org_env_alpha(t_env *env);
void	print_org_env(t_env *env);
void	handle_invalid_key(char *key, char *value);
void	env_update(t_env *env, char *key, char *value, bool has_equal);

//bi_export.c - 5 functions //
bool	is_valid_key(char *key);
void	bi_export(t_env *env, char **user_input);
void	env_add(t_env *env, char *key, char *value, bool has_equal);
void	process_key_value(t_env *env, char *key, char *value, bool has_equal);
void	process_key_value(t_env *env, char *key, char *value, bool has_equal);

//bi_pwd.c - 1 function //
void	bi_pwd(void);

//bi_unset.c - 2 functions //
void	bi_unset(char **user_input, t_env *env);
void	env_remove(t_env *env, char *key);

//================================ |ms_env| =====================================================//

//ev_env_manager.c - 1 function //
t_env	*env_manager(t_env *env);

//ev_print_env.c - 2 functions //
void	print_env(t_env *env);
void	update_shell_level(void);

//ev_env_to_struct.c - 2 functions //
t_env	*env_to_struct(char **environ);
char	**split_once(char *input, char c);

//ev_utils.c - 4 functions //
int		listsize(t_env *env);
t_env	*list_last(t_env *lst);
void	free_env_struct(t_env *env);
void	listadd_back(t_env **lst, t_env *new);

//================================ |ms_main| =====================================================//

//ms_main.c - 1 function //
int		main(void);

//ms_utils.c - 2 functions //
int		count_args(char **commands);
void	ms_print_fd(char *str, int fd);

//ms_free.c - 1 functions //
void	ms_free(t_env *env, char *input, char **commands, t_token *tokens);

//ms_exec.c - 1 function //
void	ms_exec(char *input, t_env *env);

//=========================================================================================

#endif
