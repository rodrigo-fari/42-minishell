/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at_execute_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:58:16 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/18 20:10:35 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_forked_cmd(t_ast_node *node, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		bi_exec(node->args, env);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
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
