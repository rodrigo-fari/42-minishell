/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:13:46 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/19 15:21:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	execute_pipe_command(char **command, t_env *env, int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	if (fd_out != -1)
		dup2(fd_out, 1);
	close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	bi_exec(env, token_to_struct(command), command);
	perror("execvp");
	exit(1);
} */

void	execute_pipe_command(char **command, t_env *env, int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	if (fd_out != -1)
		dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	bi_exec(env, token_to_struct(command), command);
	perror("execvp");
	exit(EXIT_FAILURE);
}

void	nfork_process(char **command, t_env *env, int fd_in, int has_next)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	if ((pid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		close (fd[0]);
		execute_pipe_command(
			command, env, fd_in, has_next ? fd[1] : -1);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
	}
}

void	execute_pipeline(char ***commands, t_env *env)
{
	int	i;
	int	fd_in;

	i = 0;
	fd_in = 0;
	while (commands[i] != NULL)
	{
		nfork_process(commands[i], env, fd_in, commands[i + 1] != NULL);
		fd_in = fd_in ? fd_in : 0;
		i++;
	}
}
