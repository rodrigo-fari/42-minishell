/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_print_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:51:45 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/08 13:44:54 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	t_token	*token_tmp;
	int		i;

	token_tmp = token;
	printf("------------------------------\n");
	i = 1;
	while (token_tmp)
	{
		printf("Token[%d] = %s\n", i, token_tmp->value);
		token_tmp = token_tmp->next;
		i++;
	}
	printf("------------------------------\n");
}
