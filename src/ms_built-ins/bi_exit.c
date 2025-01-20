/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:22:57 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/20 12:59:10 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(t_token *tokens, t_env *env, char **commands)
{
	if (tokens)
	{
		free_token_struct(tokens);
		tokens = NULL;
	}
	if (commands)
	{
		free_splits(commands);
		commands = NULL;
	}
	if (env)
	{
		free_env_struct(env);
		env = NULL;
		env_manager(env);
	}
	printf("exit\n");
	exit(0);
}
