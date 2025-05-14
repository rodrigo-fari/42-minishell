/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cc_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:06:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 21:41:17 by rde-fari         ###   ########.fr       */
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

void	cleanup_shell(t_shell *shell)
{
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->ast_root)
		free_ast(shell->ast_root);
	if (shell->env_list)
		free_env_list(shell->env_list);
	if (shell->envp)
		free_envp(shell->envp);
	free(shell);
}
