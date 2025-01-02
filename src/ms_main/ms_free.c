/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:24:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 14:18:20 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free(t_env *env, char *input, char **commands, t_token *tokens)
{
	if (tokens)
		free_token_struct(tokens);
	if (env)
		free_env_struct(env);
	if (input)
		free(input);
	if (commands)
		free_splits(commands);
	return ;
}
