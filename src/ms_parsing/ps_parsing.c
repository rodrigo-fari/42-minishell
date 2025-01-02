/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:43:40 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 12:44:28 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ps_parsing(char **commands, int i)
{
	while (commands[i])
	{
		if (!parse_quotes(commands[i]))
			return (false);
		i++;
	}
	if (!parse_redin(commands))
		return (false);
	if (!parse_redout(commands))
		return (false);
	if (!parse_pipes(commands))
		return (false);
	return (true);
}

bool	quote_verifier(char *input)
{
	if (input[0] && (input[0] == '\"' || input[0] == '\"'))
		return (true);
	else
		return (false);
}
