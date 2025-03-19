/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:19:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/19 14:59:15 by rde-fari         ###   ########.fr       */
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
# define CLEAR_CODE	"\033[2J\033[H"
# define RESET		"\001\033[0m\002"

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
	bool				has_equal;
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
void	exec_parent_process(pid_t pid);
void	exec_exe(t_token *tmp, t_env *env, char **commands);
void	bi_exec(t_env *env, t_token *tokens, char **commands);
void	exec_child_process(t_token *tmp, char **commands, t_env *env);

//[bi_exit.c]
int		is_numeric(const char *str);
void	bi_exit(t_token *tokens, t_env *env, char **commands);
void	handle_exit(t_token *tokens, t_env *env, char **commands);

//[!bi_export.c] 5 functions limit achived.
bool	is_valid_key(char *str);
void	print_org_env(t_env *env);
void	bi_export(t_env *env, char **user_input);
void	env_add(t_env *env, char *key, char *value, bool has_equal);
void	env_update(t_env *env, char *key, char *value, bool has_equal);

//[bi_export_2.c]
void	org_env_alpha(t_env *env);

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
char	**array_envs(t_env *envs);
void	free_env_struct(t_env *env);
void	listadd_back(t_env **lst, t_env *new);

//=====================================| ms_main |
//[ms_utils.c]
int		count_args(char **commands);
void	ms_print_fd(char *str, int fd);

//[ms_exec.c]
void	ms_exec(char *input, t_env *env);

//[ms_process.c]
void	exec_parent_process(pid_t pid);
void	exec_exe(t_token *tmp, t_env *env, char **commands);
void	exec_child_process(t_token *tmp, char **commands, t_env *env);

//[ms_free.c]
void	ms_free(t_env *env, char *input, char **commands, t_token *tokens);

//=====================================| ms_parsing |
//[ps_error.c]
void	ps_error(char *str);

//[ps_expand_exit_status.c]
void	expand_exit(char **commands);
void	replace_exit_status(char **commands, int i);
void	replace_exit_status_in_command(char **command);
void	replace_exit_status_at_pos(char **command, char *pos);

//[ps_expand_variable.c]
char	*var_expand(char *input);

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

//[ps_remove_quotes.c]
void	quote_fix(char **commands);
char	*verify_quotes(char *input);
char	*remove_quotes(char *input);
char	*replace_values(char *input, int i,char current_quote, bool key);
char	*remove_quotes_and_expand(char *input, int start, char current_quote);

//[ps_remove_quotes_utils.c]
bool	bool_changer(bool key);
char	*append_char_to_string(char* str, char c);

//=====================================| ms_pipeline |
//[pp_exec.c]
void	execute_pipeline(char ***commands, t_env *env);
void	execute_pipeline(char ***commands, t_env *env);
void	create_and_fork_process(char **command, t_env *env, int fd_in, int has_next);

//[pp_pipeline.c]
int		count_pipes(char **commands);
int		contains_pipe(char **commands);
void	free_pipeline(char ***pipeline);
char	***split_by_pipe(char **commands);

//=====================================| ms_redirects |
//[re_exec.c]_
void	handle_redirects(t_token *tokens);

//[re_redirect.c]
void	redirect_input(const char *file);
void	redirect_error(const char *file, int append);
void	redirect_output(const char *file, int append);

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
