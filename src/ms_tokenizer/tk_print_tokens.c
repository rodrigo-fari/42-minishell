/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:51:45 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/28 17:20:17 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token_tmp)
{
	printf("\n\nFUNCAO PRINT TOKENS:\n\n");
	printf("------------------------------");
	printf(" \n");
	while (token_tmp->next)
	{
		printf("token = %s\n", token_tmp->value);
		token_tmp = token_tmp->next;
	}
	printf("------------------------------\n");
}
