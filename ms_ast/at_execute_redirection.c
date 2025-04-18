/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_execute_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:14 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/18 20:09:28 by rde-fari         ###   ########.fr       */
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

	if (!node->right || !node->right->args || !node->right->args[0])
		return ;
	filename = node->right->args[0];
	fd = get_redir_fd(node, filename);
	if (fd == -1)
		return (perror("open"));
	pid = fork();
	if (pid == 0)
	{
		handle_redir_fd(node, fd);
		if (node->left)
			execute_ast(node->left, env);
		exit(EXIT_SUCCESS);
	}
	close(fd);
	waitpid(pid, NULL, 0);
}
