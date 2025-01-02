/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:49:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:43:52 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_to_struct(char **commands)
{
	t_token	*head;
	t_token	*current;
	int		i;

	head = NULL;
	i = 0;
	while (commands[i])
	{
		current = ft_calloc(1, sizeof(t_token));
		current->value = ft_strdup(commands[i]);
		current->type = token_type(commands[i]);
		current->next = NULL;
		tk_listadd_back(&head, current);
		i++;
	}
	return (head);
}

int	token_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (token[0] == '|')
			return (TOKEN_PIPE);
		else if (token[0] == '<')
			return (TOKEN_REDIR_IN);
		else if (token[0] == '>')
			return (TOKEN_REDIR_OUT);
	}
	else if (ft_strlen(token) == 2)
	{
		if (token[0] == '>' && token[1] == '>')
			return (TOKEN_REDIR_APPEND);
		else if (token[0] == '<' && token[1] == '<')
			return (TOKEN_REDIR_HEREDOC);
	}
	if (ft_strchr(token, '$'))
		return (TOKEN_ENV_VAR);
	else
		return (TOKEN_WORD);
}
