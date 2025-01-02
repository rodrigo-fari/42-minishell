/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:51:45 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:05:28 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token_tmp)
{
	int	i;

	i = 0;
	printf("------------------------------\n");
	while (token_tmp)
	{
		printf("[%d]Token = %s\n", i, token_tmp->value);
		token_tmp = token_tmp->next;
		i++;
	}
	printf("------------------------------\n");
}
