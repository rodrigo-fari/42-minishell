/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/28 17:22:05 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{
	char	**commands;
	t_token	*tokens;
	t_token	*tmp;
	
	(void)env;
	commands = tk_splitter(input, 0, 0);
	remove_quotes(commands);
	printf(CLEAR_CODE" "RESET);
	tokens = token_to_struct(commands);
	tmp = tokens;
	print_tokens(tmp);
	if (!ps_parsing(commands, 0))
		ms_free(env, input, commands);
	//bi_exec(commands, env);
	free(input);
	free_splits(commands);
	return ;
}
