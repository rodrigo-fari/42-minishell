/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/18 10:28:51 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{
	char	**commands;
	t_token	*tokens;

	commands = tk_splitter(input, 0, 0);
	if (!ps_parsing(commands, 0))
	{
		ms_free(NULL, input, commands, NULL);
		return;
	}
	remove_quotes(commands);
	expand_exit(commands); //Necessario correcao. Alguns codigos de saida estao diferentes do BASH.
	tokens = token_to_struct(commands);
	print_tokens(tokens);
	if (contains_pipe(commands))
	{
		char ***pipeline = split_by_pipe(commands);
		execute_pipeline(pipeline, env);
		free_pipeline(pipeline);
	}
	else
		bi_exec(env, tokens, commands);
	ms_free(NULL, input, commands, tokens);
	return;
}
