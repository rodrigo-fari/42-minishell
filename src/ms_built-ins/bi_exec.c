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

void	bi_exec(t_env *env, t_token *tokens, char **commands)
{
	t_token	*tmp;

	tmp = tokens;
	env = env_manager(NULL);
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
