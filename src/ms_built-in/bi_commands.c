/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:18:50 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 19:00:01 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_builtins(char **user_input, t_env *env)
{
	if (ft_strcmp(user_input[0], "echo") == 0)
		bi_echo(user_input);
	if (ft_strcmp(user_input[0], "pwd") == 0)
		bi_pwd();
	else
		exec_commands(user_input[0], user_input, env);
}

void	exec_commands(char *command, char **user_input, t_env *env)
{
	bool	absolute;
	pid_t	execve_new_process;

	absolute = false;
	if (ft_strchr(command, '/'))
		absolute = true;
	execve_new_process = fork();
	if (absolute == true)
	{
		if (execve_new_process)
			execve(command, user_input, NULL);
	}
	else
	{
		command = ft_strjoin("/bin/", command);
		if (execve_new_process)
			execve(command, user_input, NULL);
	}
	(void)env;
	//Criar variavel global para ultilizar o waitpid
	//Saber como funciona o wait pid
	//waitpid ira aguardar que o processo filho termine sua execução
	//pois o execve apos o termino de sua execução ele termina o processo
	//e se esse processo for o minishel, ja sabe ne ?
}
