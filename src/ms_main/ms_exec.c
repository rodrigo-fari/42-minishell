/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:19:43 by rde-fari          #+#    #+#             */
/*   Updated: 2026/03/03 00:59:55 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec(char *input, t_env *env)
{
	char		**commands;
	t_token		*tokens;
	t_ast_node	*ast_root;
	t_shell		*shell;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	get_current_directory(cwd);
	free(cwd);
	commands = tk_splitter(input, 0, 0);
	if (!pasring_verify(commands, input))
		return ;
	tokens = token_to_struct(commands, 0);
	free_splits(commands);
	quote_fix(tokens);
	ast_root = build_ast(tokens);
	shell = shell_atributes(env, tokens, ast_root);
	if (collect_all_heredocs(ast_root))
	{
		cleanup_heredocs(ast_root);
		return ;
	}
	execute_and_clean(ast_root, tokens, env);
	return ;
}

t_shell	*shell_atributes(t_env *env, t_token *tokens, t_ast_node *ast_root)
{
	t_shell	*shell;

	shell = get_shell();
	shell->tokens = tokens;
	shell->ast_root = ast_root;
	shell->env_list = env;
	return (shell);
}

void	execute_and_clean(t_ast_node *ast_root, t_token *tokens, t_env *env)
{
	t_shell	*shell;

	shell = get_shell();
	execute_ast(ast_root, env, tokens, 0);
	cleanup_heredocs(ast_root);
	cc_shell(shell, false, true, false);
}
