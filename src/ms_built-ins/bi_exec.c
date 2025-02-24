/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:18:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/24 17:07:32 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exec(t_env *env, t_token *tokens, char **commands)
{
	t_token	*tmp;

	tmp = tokens;
	env = env_manager(NULL);
	handle_redirects(tokens);
	if (ft_strcmp(tmp->value, "echo") == 0)
		bi_echo(tmp);
	else if (ft_strcmp(tmp->value, "pwd") == 0)
		bi_pwd();
	else if (ft_strcmp(tmp->value, "exit") == 0)
		bi_exit(tokens, env, commands);
	else if (ft_strcmp(tmp->value, "env") == 0)
		print_env(env);
	else if (ft_strcmp(tmp->value, "cd") == 0)
		bi_cd(commands, env);
	else if (ft_strcmp(tmp->value, "unset") == 0)
		bi_unset(commands, env);
	else if (ft_strcmp(tmp->value, "export") == 0)
		bi_export(env, commands);
	else
		exec_exe(tmp, env, commands);
}

void	exec_child_process(t_token *tmp, char **commands, t_env *env)
{
	char	*full_command;
	char	**envs_array;

	envs_array = array_envs(env);
	if (ft_strchr(tmp->value, '/'))
		execve(tmp->value, commands, envs_array);
	else
	{
		full_command = ft_strjoin("/bin/", tmp->value);
		execve(full_command, commands, envs_array);
		free(full_command);
	}
	bi_error("bash: command not found");
	ms_free(env, NULL, commands, tmp);
	exit(127);
}

void	exec_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
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
