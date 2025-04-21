/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 16:34:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{
	char		**commands;
	t_token		*tokens;
	t_ast_node	*ast_root;

	commands = tk_splitter(input, 0, 0);
	ft_print_array(commands);
	if (!ps_parsing(commands, 0))
	{
		ms_free(NULL, input, commands, NULL);
		return ;
	}
	tokens = token_to_struct(commands);
	expand_exit(tokens);
	quote_fix(tokens);
	ast_root = build_ast(tokens);
	execute_ast(ast_root, env);
	free_ast(ast_root);
	ms_free(NULL, input, commands, tokens);
	return ;
}
