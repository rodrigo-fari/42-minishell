/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:34:41 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/26 15:08:50 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void	exec_child_process(t_token *tmp, char **commands, t_env *env)
{
	char	*full_command;
	char	**envs_array;

	handle_redirects(tmp);
	envs_array = array_envs(env);
	if (ft_strchr(tmp->value, '/'))
		execve(tmp->value, commands, envs_array);
	else
	{
		full_command = ft_strjoin("/bin/", tmp->value);
		execve(full_command, commands, envs_array);
		free(full_command);
	}
	bi_error("bash: command not found\n");
	ms_free(env, NULL, commands, tmp);
	exit(127);
}

void	exec_exe(t_token *tmp, t_env *env, char **commands)
{
	pid_t	execve_new_process;

	execve_new_process = fork();
	if (execve_new_process == 0)
		exec_child_process(tmp, commands, env);
	else if (execve_new_process > 0)
		exec_parent_process(execve_new_process);
	else
		perror("fork");
}
