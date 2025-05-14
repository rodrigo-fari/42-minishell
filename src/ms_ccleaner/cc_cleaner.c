/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cc_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:06:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 22:34:31 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free(t_env *env, char *input, char **commands, t_token *tokens)
{
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env_list(env);
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
	printf("Cleaning up shell...\n");
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->ast_root)
		free_ast(shell->ast_root);
	if (shell->env_list)
		free_env_list(shell->env_list);
	if (shell->envp)
		free_envp(shell->envp);
}
