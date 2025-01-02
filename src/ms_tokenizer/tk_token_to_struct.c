/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_token_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:49:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:03:33 by rde-fari         ###   ########.fr       */
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
		current->next = NULL;
		tk_listadd_back(&head, current);
		i++;
	}
	return (head);
}
