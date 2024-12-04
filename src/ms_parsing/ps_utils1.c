/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:33 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/04 21:08:28 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_quotes(char *input)
{
	(void)input;
	//verificar aspas antes de splitar o input do usuario
}

bool	parse_syntax(char **user_input)
{
	int	i;

	if (!user_input)
		return false;
	i = 0;
	while (user_input[i])
	{
		
	}
	return (true);
}
