/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:36:57 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/07 19:44:00 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_redir_node(t_ast_node *node)
{
	if (!node->right || !node->right->args || !node->right->args[0])
	{
		ft_putstr_fd("Minishell: missing redirection target\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	process_redirection(t_ast_node *node, char *filename)
{
	int	fd;

	if (node->type == TOKEN_HEREDOC)
	{
		ft_putstr_fd("Minishell: heredoc not fully implemented\n",
			STDERR_FILENO);
		return (0);
	}
	fd = get_redir_fd(node, filename);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		perror(filename);
		return (0);
	}
	handle_redir_fd(node, fd);
	return (1);
}

int	apply_redirections(t_ast_node *node)
{
	char	*filename;

	if (!node || !is_redir(node->type))
		return (1);
	if (node->left && is_redir(node->left->type))
		if (!apply_redirections(node->left))
			return (0);
	if (!validate_redir_node(node))
		return (0);
	filename = node->right->args[0];
	return (process_redirection(node, filename));
}

void	handle_redir_fd(t_ast_node *node, int fd)
{
	if (node->type == TOKEN_REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			bi_error("Invalid input.\n");
	}
	else if (node->type == TOKEN_REDIR_OUT
		|| node->type == TOKEN_REDIR_OUT_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			bi_error("Invalid input.\n");
	}
	else if (node->type == TOKEN_REDIR_ERR
		|| node->type == TOKEN_REDIR_ERR_APPEND)
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
