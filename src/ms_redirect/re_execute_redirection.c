/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_execute_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/12 22:18:39 by rde-fari         ###   ########.fr       */
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

	if (!apply_redirections(node, 0))
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

void	execute_redirection(t_ast_node *node, t_env *env)
{
	int		in;
	int		out;
	int		err;
	pid_t	pid;
	int		status;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	err = dup(STDERR_FILENO);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_exit_status = 1;
		return ;
	}
	if (pid == 0)
		child_process(node, env);
	waitpid(pid, &status, 0);
	restore_std_fds(in, out, err);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
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
