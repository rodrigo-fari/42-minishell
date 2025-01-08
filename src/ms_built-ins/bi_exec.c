/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:18:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/08 17:04:37 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exec(t_env *env, t_token *tokens, char **commands)
{
	t_token	*tmp;

	(void)env;
	tmp = tokens;
	env = env_manager(NULL);
	// if (ft_strcmp(tmp->value, "echo") == 0)
	// 	bi_echo(tmp);
	// else if (ft_strcmp(tmp->value, "pwd") == 0)
	// 	bi_pwd();
	if (ft_strcmp(tmp->value, "exit") == 0)
		bi_exit(tmp, env, commands);
	else if (ft_strcmp(tmp->value, "env") == 0)
	print_env();
	// else if (ft_strcmp(tmp->value, "cd") == 0)
	// 	bi_cd(tmp, env);
	// else if (ft_strcmp(tmp->value, "unset") == 0)
	// 	bi_unset(tmp, env);
	// else if (ft_strcmp(tmp->value, "export") == 0)
	// 	bi_export(env, tmp);
		else
	exec_exe(tmp, env, commands);
}

void	exec_exe(t_token *tmp, t_env *env, char **commands)
{
	char	*full_command;
	pid_t	execve_new_process;
	int		status;

	execve_new_process = fork();
	if (execve_new_process == 0)
	{
		if (ft_strchr(tmp->value, '/'))
			execve(tmp->value, commands, NULL);
		else
		{
			full_command = ft_strjoin("/bin/", tmp->value);
			printf("full_command= %s\n", full_command);
			execve(full_command, commands, NULL);
			free(full_command);
		}
		bi_error("bash: command not found");
		ms_free(env, NULL, commands, tmp);
	}
	else if (execve_new_process > 0)
		waitpid(execve_new_process, &status, 0);
	else
		perror("fork");
	(void)env;
}
