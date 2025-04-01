/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:18:54 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/18 13:38:03 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void bi_exec(t_env *env, t_token *tokens, char **commands)
{
    (void)tokens;
    if (is_builtin(commands[0]))
    {
        // Handle built-in commands
/*         execute_builtin(commands, env);
 */    }
    else
    {
        // Handle external commands
        char *executable = find_executable(commands[0], env);
        if (!executable)
        {
            fprintf(stderr, "minishell: command not found: %s\n", commands[0]);
            exit(127);
        }

        execve(executable, commands, array_envs(env));
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

/* void execute_builtin(char **commands, t_env *env)
{
    if (ft_strcmp(commands[0], "echo") == 0)
        bi_echo(commands);
    else if (ft_strcmp(commands[0], "pwd") == 0)
        bi_pwd();
    else if (ft_strcmp(commands[0], "exit") == 0)
        bi_exit(NULL, env, commands);
    else if (ft_strcmp(commands[0], "env") == 0)
        print_env(env);
    else if (ft_strcmp(commands[0], "cd") == 0)
        bi_cd(commands, env);
    else if (ft_strcmp(commands[0], "unset") == 0)
        bi_unset(commands, env);
    else if (ft_strcmp(commands[0], "export") == 0)
        bi_export(env, commands);
} */