/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:02:42 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/30 23:51:47 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_child1(int *pipefd, t_ast_node *left, t_env *env)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_ast(left, env);
	exit(g_exit_status);
}

void	pipe_child2(int *pipefd, t_ast_node *right, t_env *env)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	execute_ast(right, env);
	exit(g_exit_status);
}

void	execute_pipe(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(pipefd) == -1)
	{
		g_exit_status = 1;
		return ;
	}
	pid1 = fork();
	if (pid1 == 0)
		pipe_child1(pipefd, left, env);
	pid2 = fork();
	if (pid2 == 0)
		pipe_child2(pipefd, right, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		g_exit_status = WEXITSTATUS(status2);
	else
		g_exit_status = 1;
}
