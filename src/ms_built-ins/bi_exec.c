/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:18:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:46:44 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exec(char **commands, t_env *env, t_token *tokens)
{
	env = env_manager(NULL);
	if (ft_strcmp(commands[0], "echo") == 0)
		bi_echo(commands);
	else if (ft_strcmp(commands[0], "pwd") == 0)
		bi_pwd();
	else if (ft_strcmp(commands[0], "exit") == 0)
		bi_exit(commands, env, tokens);
	else if (ft_strcmp(commands[0], "env") == 0)
		print_env();
	else if (ft_strcmp(commands[0], "cd") == 0)
		bi_cd(commands, env);
	else if (ft_strcmp(commands[0], "unset") == 0)
		bi_unset(commands, env);
	else if (ft_strcmp(commands[0], "export") == 0)
		bi_export(env, commands);
	else
		exec_exe(commands[0], commands, env);
}

void	exec_exe(char *command, char **user_input, t_env *env)
{
	char	*full_command;
	pid_t	execve_new_process;
	int		status;

	execve_new_process = fork();
	if (execve_new_process == 0)
	{
		if (ft_strchr(command, '/'))
			execve(command, user_input, NULL);
		else
		{
			full_command = ft_strjoin("/bin/", command);
			execve(full_command, user_input, NULL);
			free(full_command);
		}
		perror("execve");
		bi_exit(user_input, env, NULL);
	}
	else if (execve_new_process > 0)
		waitpid(execve_new_process, &status, 0);
	else
		perror("fork");
	(void)env;
}
