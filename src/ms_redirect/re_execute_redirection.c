/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_execute_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/07 19:06:40 by rde-fari         ###   ########.fr       */
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

void execute_redirection(t_ast_node *node, t_env *env)
{
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stderr = dup(STDERR_FILENO);
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_exit_status = 1;
		return;
	}
	
	if (pid == 0)
	{
		// Child process
		// Apply all redirections in the chain, starting from the outermost one (node)
		// This will recursively apply all redirections in the chain
		if (!apply_redirections(node))
		{
			exit(EXIT_FAILURE);
		}
		
		// Find and execute the command node
		t_ast_node *cmd = find_command_node(node);
		if (cmd)
		{
			if (cmd->args && cmd->args[0])
			{
				if (is_builtin(cmd->args[0]))
					execute_builtin(cmd->args, env);
				else
					bi_exec(cmd->args, env);
			}
		}
		
		exit(g_exit_status);
	}
	else
	{
		// Parent process
		waitpid(pid, &status, 0);
		
		// Restore original file descriptors
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		close(saved_stderr);
		
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

// Helper function to apply a single redirection and its chain recursively
int apply_redirections(t_ast_node *node)
{
	if (!node)
		return 1;
	
	if (!is_redir(node->type))
		return 1; // Not a redirection node
	
	// For AST with nested redirections like:
	// > c
	// +-- > b
	//     +-- > a
	//         +-- echo 42
	
	// First, recursively apply any nested redirections in the left branch
	if (node->left && is_redir(node->left->type))
	{
		if (!apply_redirections(node->left))
			return 0;
	}
	
	// Then apply this redirection
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ft_putstr_fd("Minishell: missing redirection target\n", STDERR_FILENO);
		return 0;
	}
	
	char *filename = node->right->args[0];
	int fd;
	
	if (node->type == TOKEN_HEREDOC)
	{
		// Heredoc handling
		ft_putstr_fd("Minishell: heredoc not fully implemented\n", STDERR_FILENO);
		return 0;
	}
	else
	{
		fd = get_redir_fd(node, filename);
		if (fd == -1)
		{
			// Print better error message with filename
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			perror(filename);
			return 0;
		}
		
		// Apply the redirection
		handle_redir_fd(node, fd);
		// NOTE: handle_redir_fd already closes fd after dup2
	}
	
	return 1;
}

// Find the command node at the end of the redirection chain
t_ast_node *find_command_node(t_ast_node *node)
{
	if (!node)
		return NULL;
	
	if (!is_redir(node->type))
		return node;
	
	// For redirection nodes, the command is in the left branch
	if (node->left && !is_redir(node->left->type))
		return node->left;
	
	// Recursive case: keep searching in the left branch
	return find_command_node(node->left);
}

void	handle_redir_fd(t_ast_node *node, int fd)
{
	if (node->type == TOKEN_REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			bi_error("Invalid input.\n");
	}
	else if (node->type == TOKEN_REDIR_OUT || node->type == TOKEN_REDIR_OUT_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			bi_error("Invalid input.\n");
	}
	else if (node->type == TOKEN_REDIR_ERR || node->type == TOKEN_REDIR_ERR_APPEND)
	{
		if (dup2(fd, STDERR_FILENO) == -1)
			bi_error("Invalid input.\n");
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
