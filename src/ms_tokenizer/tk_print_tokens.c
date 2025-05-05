/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:51:45 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/05 20:56:23 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_type_str(t_type type)
{
	const char	*type_str[] = {
		"TOKEN_WORD",
		"TOKEN_PIPE",
		"TOKEN_REDIR_IN",
		"TOKEN_REDIR_OUT",
		"TOKEN_REDIR_OUT_APPEND",
		"TOKEN_REDIR_ERR",
		"TOKEN_REDIR_ERR_APPEND",
		"TOKEN_ENV_VAR",
		"TOKEN_CMD",
		"TOKEN_FILENAME",
		"TOKEN_HEREDOC"
	};

	if (type >= 0 && type <= TOKEN_HEREDOC)
		return (type_str[type]);
	return ("TOKEN_UNKNOWN");
}

void	print_tokens(t_token *token)
{
	t_token	*token_tmp;
	int		i;

	token_tmp = token;
	i = 1;
	while (token_tmp)
	{
		printf("TK_I[%d] = \"%s\"\n", i, token_tmp->value);
		printf("TK_T[%d] = %s\n", i, get_token_type_str(token_tmp->type));
		printf("============================\n");
		token_tmp = token_tmp->next;
		i++;
	}
}