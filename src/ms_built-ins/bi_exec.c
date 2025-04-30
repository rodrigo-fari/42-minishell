/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:18:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/30 21:45:40 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_command_path(const char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;


	if (ft_strcmp((char *)cmd, "./minishell") == 0)
		update_shell_level();
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_splits(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_splits(paths); 
	return (NULL);
}

void bi_exec(char **commands, t_env *env)
{
	struct stat file_stat;
	char *command_path;

	while (commands[0] && commands[0][0] == '\0')
		commands++;
	if (!commands[0] || commands[0][0] == '\0')
	{
		g_exit_status = 0;
		return ;
	}
	if (is_builtin(commands[0]))
	{
		execute_builtin(commands, env);
		return ;
	}
	command_path = resolve_command_path(commands[0], env);
	if (!command_path)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127;
		exit(g_exit_status);
	}

	if (stat(command_path, &file_stat) == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		if (ft_strchr(commands[0], '/'))
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			g_exit_status = 126;
			exit(g_exit_status);
		}
		else
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			g_exit_status = 127;
			exit(g_exit_status);
		}
	}
	if (access(command_path, X_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127;
		exit(g_exit_status);
	}
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
