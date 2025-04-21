/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_execute_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 22:50:45 by rde-fari         ###   ########.fr       */
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

void	execute_redirection(t_ast_node *node, t_env *env)
{
	int		fd;
	pid_t	pid;
	char	*filename;
	int		status;

	if (!node->right || !node->right->args || !node->right->args[0])
	{
		g_exit_status = 1; // Set to 1 if no filename is provided
		return ;
	}
	filename = node->right->args[0];
	fd = get_redir_fd(node, filename);
	if (fd == -1)
	{
		perror("open");
		g_exit_status = 1; // Set to 1 if file opening fails
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		handle_redir_fd(node, fd);
		if (node->left)
			execute_ast(node->left, env);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	waitpid(pid, &status, 0);

	// Set g_exit_status based on the child process exit status
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1; // Default to 1 if the process did not exit normally
}

void	handle_redir_fd(t_ast_node *node, int fd)
{
	if (node->type == TOKEN_REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			perror("dup2");
	}
	else if (node->type == TOKEN_REDIR_OUT || node->type == TOKEN_REDIR_OUT_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else if (node->type == TOKEN_REDIR_ERR || node->type == TOKEN_REDIR_ERR_APPEND)
	{
		if (dup2(fd, STDERR_FILENO) == -1)
			perror("dup2");
	}
	close(fd);
}

int	is_redir(t_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_OUT_APPEND
		|| type == TOKEN_REDIR_ERR
		|| type == TOKEN_REDIR_ERR_APPEND);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
