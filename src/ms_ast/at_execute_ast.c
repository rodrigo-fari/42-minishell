/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_execute_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:58:16 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/07 23:45:15 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_cmd(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127;
		return (0);
	}
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_exit_status = 126;
		return (0);
	}
	if (access(cmd, X_OK) == -1)
	{
		perror("Minishell");
		g_exit_status = 126;
		return (0);
	}
	return (1);
}

void    execute_forked_cmd(t_ast_node *node, t_env *env)
{
    pid_t   pid;
    int     status;

    // Skip forking if we're already in a child process (e.g., inside a pipe)
    if (node->in_pipe) 
    {
        bi_exec(node->args, env); // Execute directly in the pipe child
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        g_exit_status = 1;
    }
    else if (pid == 0)
    {
        bi_exec(node->args, env); // Child executes command
        exit(g_exit_status);
    }
    else
    {
        waitpid(pid, &status, 0); // Parent waits for child
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
    }
}

void	execute_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return ;
	if (node->type == TOKEN_PIPE)
		execute_pipe(node->left, node->right, env);
	else if (is_redir(node->type))
		execute_redirection(node, env);
	else if (is_builtin(node->args[0]))
		execute_builtin(node->args, env);
	else
		execute_forked_cmd(node, env);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->args)
		free_splits(node->args);
	free(node);
}
