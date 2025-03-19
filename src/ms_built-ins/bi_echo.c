/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:50 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/19 15:10:43 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_echo(t_token *tmp)
{
	bool	flag;

	flag = true;
	while (tmp)
	{
		tmp = tmp->next;
		while (tmp && flag_verify(tmp->value))
		{
			flag = false;
			if (!tmp->next)
				return ;
			else
				tmp = tmp->next;
		}
		while (tmp)
		{
			ms_print_fd(tmp->value, 1);
			if (tmp->next)
				ms_print_fd(" ", 1);
			tmp = tmp->next;
		}
	}
	if (tmp == NULL && flag)
		ms_print_fd("\n", 1);
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
