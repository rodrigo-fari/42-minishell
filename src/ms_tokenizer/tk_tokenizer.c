/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:49:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/05 20:58:49 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Determina o tipo de token com base no valor da string
int	token_type(char *token)
{
	if (ft_strncmp(token, "2>>", 3) == 0)
		return (TOKEN_REDIR_ERR_APPEND);
	else if (ft_strncmp(token, "2>", 2) == 0)
		return (TOKEN_REDIR_ERR);
	else if (ft_strncmp(token, ">>", 2) == 0)
		return (TOKEN_REDIR_OUT_APPEND);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIR_OUT);
	else if (ft_strchr(token, '$'))
		return (TOKEN_ENV_VAR);
	else
		return (TOKEN_WORD);
}

// Converte um array de strings em uma lista ligada de tokens
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
		if (!current)
			return (NULL); // Lida com erro de alocação
		current->value = ft_strdup(commands[i]);
		if (!current->value)
		{
			free(current);
			return (NULL); // Lida com erro de duplicação
		}
		current->type = token_type(commands[i]);
		current->next = NULL;
		tk_listadd_back(&head, current);
		i++;
	}
	return (head);
}
