/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:39:05 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/14 20:08:50 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	node_has_in_redir(t_ast_node *node)
{
	while (node)
	{
		if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_HEREDOC)
			return (1);
		node = node->left;
	}
	return (0);
}
