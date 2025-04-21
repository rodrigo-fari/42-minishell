/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:24:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 16:28:31 by rde-fari         ###   ########.fr       */
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
	{
		free(input);
		input = NULL;
	}
	if (commands)
		free_splits(commands);
	return ;
}
