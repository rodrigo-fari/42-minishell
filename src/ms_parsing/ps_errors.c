/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:33 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 13:25:31 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_hand(char *str)
{
	printf(RED"[Error]"RESET);
	printf("%s\n", str);
}

//mensagens de erro recisam ser enviadas para o stderror
//ultilizar porinquanto esta função