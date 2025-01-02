/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 14:18:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{
	char	**commands;
	t_token	*tokens;
	t_token	*tmp;

	commands = tk_splitter(input, 0, 0);
	if (!ps_parsing(commands, 0))
		ms_free(NULL, input, commands, NULL);
	remove_quotes(commands);
	tokens = token_to_struct(commands);
	free(input);
	free_splits(commands);
	tmp = tokens;
	print_tokens(tmp);
	bi_exec(env, tokens);
	return ;
}
