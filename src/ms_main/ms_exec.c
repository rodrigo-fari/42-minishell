/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 22:16:40 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{
	char		**commands;
	t_token		*tokens;
	t_ast_node	*ast_root;

	commands = tk_splitter(input, 0, 0);
	if (!ps_parsing(commands, 0))
	{
		ms_free(NULL, input, commands, NULL);
		return ;
	}
	tokens = token_to_struct(commands);
	free_splits(commands);
	quote_fix(tokens);
	ast_root = build_ast(tokens);
	execute_ast(ast_root, env);
	free_ast(ast_root);
	ms_free(NULL, input, NULL, tokens);
	return ;
}

void	print_ast(t_ast_node *tmp)
{
	int	i;

	i = 0;
	printf("AST NODE + VALUES:\n");
	while (tmp)
	{
		printf("TID[%d]\nTTYPE[%s]\n", i, get_token_type_str(tmp->type));
		if (tmp->left)
			printf("LEFT_TKN[%s]\n", get_token_type_str(tmp->left->type));
		if (tmp->right)
			printf("RIGHT_TKN[%s]\n", get_token_type_str(tmp->right->type));
		if (tmp->args)
			ft_print_array(tmp->args);
		tmp = tmp->right;
		i++;
	}
}
