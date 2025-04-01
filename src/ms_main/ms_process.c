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

void exec_exe(t_token *token, t_env *env, char **args)
{
    char *path = find_executable(token->value, env);
    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", token->value);
        return;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        // Child process
        t_env *helper_env = env_manager(NULL);
        char **env_crianca = array_envs(helper_env);
        execve(path, args, env_crianca);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    free(path);
}

char *find_executable(const char *cmd, t_env *env)
{
    char *path_env = NULL;
    char *path = NULL;
    char *dir;
    char *saveptr;
    char full_path[1024];
    struct stat st;

    // First, check if the command contains a '/'
    if (strchr(cmd, '/') != NULL)
    {
        // If it does, it's a direct path. Just check if it's executable.
        if (access(cmd, X_OK) == 0)
        {
            return strdup(cmd);
        }
        return NULL;
    }

    // Get the PATH environment variable
    while (env)
    {
        if (strcmp(env->key, "PATH") == 0)
        {
            path_env = strdup(env->value);
            break;
        }
        env = env->next;
    }

    if (!path_env)
    {
        return NULL;  // PATH not found in environment
    }

    // Tokenize the PATH
    dir = strtok_r(path_env, ":", &saveptr);
    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);

        // Check if the file exists and is executable
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            path = strdup(full_path);
            break;
        }

        dir = strtok_r(NULL, ":", &saveptr);
    }

    free(path_env);
    return path;
}