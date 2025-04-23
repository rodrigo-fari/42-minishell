/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:18:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/24 00:03:28 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *resolve_command_path(const char *cmd, t_env *env)
{
    char *path_env;
    char **paths;
    char *full_path;
    char *temp;
    int i;

    // Se o comando contém '/', trate-o como um caminho
    if (ft_strchr(cmd, '/'))
        return (ft_strdup(cmd));

    // Obter a variável de ambiente PATH
    path_env = get_env_value(env, "PATH");
    if (!path_env)
        return (NULL);

    // Dividir o PATH em diretórios
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);

    // Procurar o comando em cada diretório
    i = 0;
    while (paths[i])
    {
        temp = ft_strjoin(paths[i], "/"); // Adicionar '/' ao diretório
        full_path = ft_strjoin(temp, cmd); // Concatenar o comando
        free(temp); // Liberar a string temporária

        if (access(full_path, X_OK) == 0) // Verificar se o comando é executável
        {
            free_splits(paths);
            return (full_path);
        }
        free(full_path); // Liberar o caminho completo se não for válido
        i++;
    }
    free_splits(paths);
    return (NULL);
}

void bi_exec(char **commands, t_env *env)
{
	struct stat file_stat;
	char *command_path;

	// Skip empty tokens (e.g., when $EMPTY is empty)
	while (commands[0] && commands[0][0] == '\0')
		commands++;

	// Check if the command is empty after skipping
	if (!commands[0] || commands[0][0] == '\0')
	{
		// If the command is empty, do nothing and return
		g_exit_status = 0; // No error for empty command
		return;
	}

	// Check if the command is a built-in
	if (is_builtin(commands[0]))
	{
		execute_builtin(commands, env);
		return;
	}

	// Resolve the command path
	command_path = resolve_command_path(commands[0], env);
	if (!command_path)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127; // Command not found
		exit(g_exit_status);
	}

	// Check if the file exists
	if (stat(command_path, &file_stat) == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127; // Command not found
		exit(g_exit_status);
	}

	// Check if the file is a directory
	if (S_ISDIR(file_stat.st_mode))
	{
		// If explicitly executed (e.g., ./test_files), treat as "is a directory"
		if (ft_strchr(commands[0], '/'))
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			g_exit_status = 126; // Is a directory
			exit(g_exit_status);
		}
		else
		{
			// Otherwise, treat as "command not found"
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			g_exit_status = 127; // Command not found
			exit(g_exit_status);
		}
	}

	// Check if the file is executable
	if (access(command_path, X_OK) == -1)
	{
		// If the file is not executable, treat as "command not found"
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_status = 127; // Command not found
		exit(g_exit_status);
	}

	// Execute the command
	env = env_manager(NULL);
	execve(command_path, commands, array_envs(env));
	perror("execve");
	g_exit_status = 1; // Set g_exit_status to 1 if execve fails
	exit(g_exit_status);
}

void execute_builtin(char **commands, t_env *env)
{
	t_token *helper;

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
