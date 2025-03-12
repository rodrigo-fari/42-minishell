/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:13:46 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/12 12:45:36 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe_command(char **command, t_env *env, int fd_in, int fd_out)
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
}

void	execute_pipeline(char ***commands, t_env *env)
{
	int i = 0;
	int fd[2];
	pid_t pid;
	int fd_in = 0;

	while (commands[i] != NULL)
	{
		pipe(fd);
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		} 
		else if (pid == 0)
		{
			close(fd[0]);
			execute_pipe_command(commands[i], env, fd_in, commands[i + 1] != NULL ? fd[1] : -1);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
			i++;
		}
	}
}