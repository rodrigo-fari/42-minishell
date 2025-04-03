/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:13:46 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/27 19:43:32 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "minishell.h"

void	execute_pipe_command(char **command, t_env *env, int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	if (fd_out != -1)
		dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	bi_exec(env, token_to_struct(command), command);
	exit(EXIT_FAILURE);
}

void	nfork_process(char **command, t_env *env, int fd_in, int has_next)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		if (has_next)
			execute_pipe_command(command, env, fd_in, fd[1]);
		else
			execute_pipe_command(command, env, fd_in, -1);
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
	int	has_next;

	i = 0;
	fd_in = 0;
	has_next = 1;
	while (commands[i] != NULL)
	{
		if (commands[i + 1] != NULL)
			nfork_process(commands[i], env, fd_in, has_next);
		if (fd_in != 0)
			fd_in = STDIN_FILENO;
		else
			fd_in = 0;
	}
}
 */