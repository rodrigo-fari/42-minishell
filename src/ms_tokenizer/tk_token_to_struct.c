/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_token_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:49:21 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/28 17:18:04 by rde-fari         ###   ########.fr       */
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
	printf("\n\nADICIONANDO COMANDO A LISTA:\n\n");
	while (commands[i])
	{
		printf("Adding command: %s\n", commands[i]); // Debug message
		current = ft_calloc(1, sizeof(t_token));
		current->value = ft_strdup(commands[i]);
		current->next = NULL;
		tk_listadd_back(&head, current);
		i++;
	}
	t_token *temp;
	temp = head;
	printf("\n\nPRINTANDO LISTA ANTES DO TOKEN_PRINT:\n\n");
	while (temp)
	{
		printf("RESULT= %s\n", temp->value);
		temp = temp->next;
	}
	return (head);
}