/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_redins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:46:00 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:44:45 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_redin(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (quote_verifier(commands[i]) && commands[i + 1])
			i++;
		if (commands[i][0] == '<' && ft_strlen(commands[i]) > 2)
		{
			ps_error("bash: syntax error near unexpected token: < || << ");
			return (false);
		}
		if (ft_strcmp(commands[i], "<") == 0
			|| ft_strcmp(commands[i], "<<") == 0)
		{
			if (!commands[i + 1] || !commands[i - 1])
			{
				ps_error("bash: syntax error near unexpected token: < || <<");
				return (false);
			}
		}
		i++;
	}
	return (true);
}
