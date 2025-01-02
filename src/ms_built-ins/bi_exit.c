/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:22:57 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:38:14 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_exit(char **commands, t_env *env, t_token *tokens)
{
	if (tokens)
		free_token_struct(tokens);
	if (commands)
		free_splits(commands);
	if (env)
		free_env_struct(env);
	printf("exit\n");
	exit(0);
}
