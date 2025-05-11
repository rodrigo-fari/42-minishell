/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:41:39 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/10 19:23:21 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_directory_error(char *command)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	g_exit_status = 126;
	exit(g_exit_status);
}

void	check_command_path(char *command_path, char **commands)
{
	struct stat	file_stat;

	if (stat(command_path, &file_stat) == -1
		|| access(command_path, X_OK) == -1)
		handle_command_not_found(commands[0]);
	if (S_ISDIR(file_stat.st_mode))
		handle_directory_error(commands[0]);
}

void	bi_exec(char **commands, t_env *env)
{
	char	*command_path;

	handle_builtin_or_empty(commands, env);
	command_path = resolve_command_path(commands[0], env);
	if (!command_path)
		handle_command_not_found(commands[0]);
	check_command_path(command_path, commands);
	env = env_manager(NULL);
	execve(command_path, commands, array_envs(env));
	perror("execve");
	g_exit_status = 1;
	exit(g_exit_status);
}

void	execute_builtin(char **commands, t_env *env)
{
	t_token	*helper;

	helper = token_to_struct(commands);
	env = env_manager(NULL);
	if (ft_strcmp(commands[0], "echo") == 0)
		bi_echo(helper);
	else if (ft_strcmp(commands[0], "pwd") == 0)
		bi_pwd();
	else if (ft_strcmp(commands[0], "exit") == 0)
		bi_exit(helper);
	else if (ft_strcmp(commands[0], "env") == 0)
		print_env(env);
	else if (ft_strcmp(commands[0], "cd") == 0)
		bi_cd(commands, env);
	else if (ft_strcmp(commands[0], "unset") == 0)
		bi_unset(commands, env);
	else if (ft_strcmp(commands[0], "export") == 0)
		bi_export(env, commands);
}
