/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:50 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/20 12:36:37 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_echo(char **args)
{
	int		i;
	bool	flag;

	flag = true;
	i = 1;
	while (args[i])
	{
		while (args[i] && flag_verify(args[i]))
		{
			flag = false;
			if (!args[i + 1])
				return ;
			else
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

bool	flag_verify(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i + 1] && (str[i + 1] != 'n' || str[i] == '-'))
				return (false);
			while (str[i] == 'n')
				i++;
		}
		else
			return (false);
	}
	return (true);
}
