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

void bi_exec(char **commands, t_env *env)
{
    env = env_manager(NULL);

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

void execute_builtin(char **commands, t_env *env)
{
    
    t_token *helper = token_to_struct(commands);
    env = env_manager(NULL);

    if (ft_strcmp(commands[0], "echo") == 0)
        bi_echo(helper);
    else if (ft_strcmp(commands[0], "pwd") == 0)
        bi_pwd();
    else if (ft_strcmp(commands[0], "exit") == 0)
        bi_exit(helper, env, commands);
    else if (ft_strcmp(commands[0], "env") == 0)
        print_env(env);
    else if (ft_strcmp(commands[0], "cd") == 0)
        bi_cd(commands, env);
    else if (ft_strcmp(commands[0], "unset") == 0)
        bi_unset(commands, env);
    else if (ft_strcmp(commands[0], "export") == 0)
        bi_export(env, commands);
}