/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:50 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 17:40:06 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_echo(char **args)
{
	int		i;
	bool	flag;

	flag = true;
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n") == 0)
		{
			flag = false;
			i++;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		if (flag)
			printf("\n");
	}
}

//Necessario corrigir leitura de flag do -n
//Ex: -nnnnnnnnn -nnnnnnn -nnnnnn -nnnnnn alow <- input valido