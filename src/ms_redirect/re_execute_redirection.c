/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_execute_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/07 23:53:23 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_fd(t_ast_node *node, char *filename)
{
	int	fd;

	fd = -1;
	if (node->type == TOKEN_REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (node->type == TOKEN_REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == TOKEN_REDIR_OUT_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == TOKEN_REDIR_ERR)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == TOKEN_REDIR_ERR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	restore_std_fds(int in, int out, int err)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	dup2(err, STDERR_FILENO);
	close(in);
	close(out);
	close(err);
}

void	child_process(t_ast_node *node, t_env *env)
{
	t_ast_node	*cmd;

	if (!apply_redirections(node))
		exit(EXIT_FAILURE);
	cmd = find_command_node(node);
	if (cmd && cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
			execute_builtin(cmd->args, env);
		else
			bi_exec(cmd->args, env);
	}
	exit(g_exit_status);
}

void execute_redirection(t_ast_node *node, t_env *env)
{
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    
    if (!apply_redirections(node)) {
        g_exit_status = 1;
    } else {
        t_ast_node *cmd = find_command_node(node);
        if (cmd) execute_ast(cmd, env);
    }
    
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

t_ast_node	*find_command_node(t_ast_node *node)
{
	if (!node)
		return (NULL);
	if (!is_redir(node->type))
		return (node);
	if (node->left && !is_redir(node->left->type))
		return (node->left);
	return (find_command_node(node->left));
}
