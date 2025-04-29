/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_execute_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:58:16 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 23:54:52 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_forked_cmd(t_ast_node *node, t_env *env)
{
	pid_t		pid;
	int			status;
	struct stat	file_stat;

	// Check if the command is an absolute or relative path
	if (ft_strchr(node->args[0], '/'))
	{
		// Check if the file exists
		if (stat(node->args[0], &file_stat) == -1)
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			g_exit_status = 127; // Command not found
			return;
		}

		// Check if the file is a directory
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			g_exit_status = 126; // Is a directory
			return;
		}

		// Check if the file is executable
		if (access(node->args[0], X_OK) == -1)
		{
			perror("Minishell");
			g_exit_status = 126; // Permission denied
			return;
		}
	}

	// Fork and execute the command
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_exit_status = 1; // Fork failed
	}
	else if (pid == 0)
	{
		bi_exec(node->args, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status); // Update g_exit_status based on child exit status
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

void	handle_command(t_ast_node **root, t_ast_node **current, t_token **token)
{
	t_ast_node	*new_node;
	int			token_count;
	t_token		*temp;
	int			i;

	new_node = create_node((*token)->type);
	if (!new_node)
		return ;
	temp = *token;
	token_count = 0;
	while (temp && !is_redir(temp->type) && temp->type != TOKEN_PIPE)
	{
		token_count++;
		temp = temp->next;
	}
	new_node->args = ft_calloc(token_count + 1, sizeof(char *));
	if (!new_node->args)
	{
		free(new_node);
		return ;
	}
	i = -1;
	while (++i < token_count)
	{
		new_node->args[i] = ft_strdup((*token)->value);
		*token = (*token)->next;
	}
	if (!*root)
		*root = new_node;
	else if ((*root)->type == TOKEN_PIPE && !(*root)->right)
		(*root)->right = new_node;
	else if (*current)
		(*current)->right = new_node;
	*current = new_node;
}
