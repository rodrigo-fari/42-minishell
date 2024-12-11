/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:50 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/11 14:20:39 by rde-fari         ###   ########.fr       */
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
			print_args(args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		if (flag)
			printf("\n");
	}
}


void	print_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\"')
			i++;
		printf("%c", str[i]);
		i++;
	}
}
