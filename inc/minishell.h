/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:08:08 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 21:43:11 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ COLORS ┃
# define RED "\001\033[1;31m\002"
# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;32m\002"
# define CYAN "\001\033[1;36m\002"
# define BLUE "\001\033[1;34m\002"
# define MAGENTA "\001\033[1;35m\002"
# define RESET "\001\033[0m\002"

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ LIBRARIES ┃
# include <stddef.h>
# include <stdbool.h>
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

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ SUPPORT DEFINITIONS ┃
# define LONG_MAX 9223372036854775807
# define LONG_MIN -9223372036854775808

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ GLOBAL VARIABLE ┃
extern int	g_exit_status;

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ STRUCTURES ┃
//【Definition of available token types】
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

//【Definition of token's node content】
typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}	t_token;

//【Definition of abstract syntax tree's node content】
typedef struct s_ast_node
{
	t_type				type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

//【Definition of environment variable's node content】
typedef struct s_env
{
	char				*key;
	char				*value;
	bool				has_equal;
	struct s_env		*next;
}	t_env;

//【Definition of a general struct, containing pointers to every single other struct】
typedef struct s_shell
{
	t_token		*tokens;
	t_ast_node	*ast_root;
	t_env		*env_list;
	char		**envp;
	int			heredoc_fd;
}	t_shell;



void		free_tokens(t_token *token);
void		free_ast(t_ast_node *node);
void		free_env_list(t_env *env);
void		free_envp(char **envp);
void		cleanup_shell(t_shell *shell);
t_shell		*get_shell(void);




//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ ABSTRACT SYNTAX TREE FUNCTIONS ┃
//【at_build_ats.c】-【5 function limit achived on this file.】
t_ast_node	*create_node(t_type type);
void		handle_pipe(t_ast_node **root, t_ast_node *new_node, t_token **token);
void		handle_heredoc(t_ast_node **root, t_token **token);
void		handle_redir(t_ast_node **root, t_token **token);
t_ast_node	*build_ast(t_token *tokens);

//【at_execute_ast.c】
int			validate_cmd(char *cmd);
void		execute_forked_cmd(t_ast_node *node, t_env *env);
void		execute_ast(t_ast_node *node, t_env *env);
void		free_ast(t_ast_node *node);

//【at_utils_ast.c】
int			count_tokens(t_token *token);
void		fill_args(t_ast_node *node, t_token **token, int count);
void		handle_command(t_ast_node **root, t_ast_node **current, t_token **token);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ BUILT-IN FUNCTIONS ┃
//【bi_cd_2.c】
void		handle_cd_error(void);
void		change_directory(const char *path, t_env *env, char *old_pwd);

//【bi_cd.c】-【5 function limit achived on this file.】
void		bi_cd(char **user_input, t_env *env);
bool		check_too_many_arguments(char **user_input);
char		*find_path_home_in_env(t_env *env);
char		*find_oldpwd_in_env(t_env *env);
void		update_pwd(t_env *env, char *old_pwd);

//【bi_echo.c】
void		bi_echo(t_token *tmp);
bool		flag_verify(char *str);

//【bi_error.c】
void		bi_error(char *str);

//【bi_exec_2.c】
void		handle_directory_error(char *command);
void		check_command_path(char *command_path, char **commands);
void		bi_exec(char **commands, t_env *env);
void		execute_builtin(char **commands, t_env *env);

//【bi_exec.c】-【5 function limit achived on this file.】
char		*check_direct_path(const char *cmd);
char		*find_executable(char **paths, const char *cmd);
char		*resolve_command_path(const char *cmd, t_env *env);
void		handle_builtin_or_empty(char **commands, t_env *env);
void		handle_command_not_found(char *command);

//【bi_exit.c】-【5 function limit achived on this file.】
void		bi_exit(t_token *token);
void		define_exit_status(char *exit_status);
bool		check_exit_arguments(t_token *token);
bool		check_exit_signals(t_token *token);
bool		check_signal_quantity(int qnt);

//【bi_export_2.c】
void		org_env_alpha(t_env *env);
void		print_org_env(t_env *env);
void		env_update(t_env *env, char *key, char *value, bool has_equal);
void		handle_invalid_key(char *key, char *value);

//【bi_export.c】-【5 function limit achived on this file.】
void		parse_key_value(char *input, char **key, char **value, bool *has_equal);
void		process_key_value(t_env *env, char *key, char *value, bool has_equal);
void		bi_export(t_env *env, char **user_input);
bool		is_valid_key(char *key);
void		env_add(t_env *env, char *key, char *value, bool has_equal);

//【bi_pwd.c】
void		bi_pwd(void);

//【bi_unset.c】
void		bi_unset(char **user_input, t_env *env);
void		env_remove(t_env *env, char *key);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ ENV FUNCTIONS ┃
//【ev_get_env.c】
t_env		*get_env(t_env *env);
void		update_shell_level(void);

//【ev_env_to_struct.c】
t_env		*env_to_struct(char **environ);
char		**split_once(char *input, char c);

//【ev_print_env.c】
void		print_env(t_env *env);

//【ev_utils.c】-【5 function limit achived on this file.】
void		listadd_back(t_env **lst, t_env *new);
t_env		*list_last(t_env *lst);
void		free_env_struct(t_env *env);
int			listsize(t_env *env);
char		**array_envs(t_env *envs);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ HEREDOC FUNCTIONS ┃
//【】
//【】
//【】
//【】

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ MAIN FUNCTIONS ┃
//【ms_exec.c】
void		ms_exec(char *input, t_env *env);
void		print_ast(t_ast_node *tmp);

//【ms_free.c】
void		ms_free(t_env *env, char *input, char **commands, t_token *tokens);

//【ms_utils.c】
void		ms_print_fd(char *str, int fd);
int			count_args(char **commands);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ PARSING FUNCTIONS ┃
//【ps_error.c】
void		ps_error(char *str);

//【ps_expand_variable.c】
char		*var_expand(char *input);

//【ps_parsing.c】
bool		ps_parsing(char **commands, int i);
bool		quote_verifier(char *input);

//【ps_pipes.c】
bool		parse_pipes(char **commands);

//【ps_quotes.c】
bool		parse_quotes(char *input, int i, int validation);

//【ps_redins.c】
bool		parse_redin(char **commands);

//【ps_redout.c】
bool		parse_redout(char **commands);

//【ps_remove_quotes_utils.c】
bool		bool_changer(bool key);
char		*extract_var_name(char *input, int *i);
char		*get_env_value(t_env *env, char *var_name);
char		*append_string_to_string(char *str1, const char *str2);

//【ps_remove_quotes.c】-【5 function limit achived on this file.】
void		quote_fix(t_token *tokens);
char		*verify_quotes(char *input);
char		*replace_values(char *input, char current_quote, bool key, t_env *env);
char		*remove_quotes_and_expand(char *input, t_env *env);
char		*remove_quotes(char *input);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ PIPELINE FUNCTIONS ┃
//【pp_execute_pipe.c】
void		pipe_child1(int *pipefd, t_ast_node *left, t_env *env);
void		pipe_child2(int *pipefd, t_ast_node *right, t_env *env);
void		execute_pipe(t_ast_node *left, t_ast_node *right, t_env *env);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ REDIRECT FUNCTIONS ┃
//【re_execute_redirection.c】-【5 function limit achived on this file.】
int			get_redir_fd(t_ast_node *node, char *filename);
void		restore_std_fds(int in, int out, int err);
void		child_process(t_ast_node *node, t_env *env);
void		execute_redirection(t_ast_node *node, t_env *env);
t_ast_node	*find_command_node(t_ast_node *node);

//【re_utils_2.c】
int			is_builtin(char *cmd);
int node_has_in_redir(t_ast_node *node);

//【re_utils.c】-【5 function limit achived on this file.】
int			validate_redir_node(t_ast_node *node);
int			apply_redirections(t_ast_node *node, int is_pipe);
int			process_redirection(t_ast_node *node, char *filename, int is_pipe);
void		handle_redir_fd(t_ast_node *node, int fd, int is_pipe);
int			is_redir(t_type type);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ SIGNAL HANDLING FUNCTIONS ┃
//【sg_sig_handling.c】
void		sig_ctrl_c(int sig);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ TOKENIZER FUNCTIONS ┃
//【tk_print_tokens.c】
char		*get_token_type_str(t_type type);
void		print_tokens(t_token *token);

//【tk_split_2.c】
int			skip_quoted_segment(char *input, int cursor);
char		*extract_word(char *input, int *i);

//【tk_split.c】-【5 function limit achived on this file.】
int			skip_quotes(char *input, int i);
int			tk_count_words(char *input, int i, int count);
char		**tk_splitter(char *input, int i, int j);
int			is_special_char(char c);
char		*extract_special_token(char *input, int *i);

//【tk_tokenizer.c】
int			token_type(char *token);
t_token		*token_to_struct(char **commands);

//【tk_utils.c】
void		tk_listadd_back(t_token **lst, t_token *new);
void		free_token_struct(t_token *token);
int			tk_listsize(t_token *token);
int			skip_whitespace(char *input, int i);

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ END IF ┃
#endif
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ END IF ┃	