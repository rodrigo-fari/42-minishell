/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/13 10:01:15 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parsing(char *input, char **input_splited)
{
	if (ft_strchr(input, '\"') != 0 || ft_strchr(input, '\'') != 0)
	{
		if (!parse_quotes(input, -1, 0, 0))
			return (false);
	}
	if (ft_strchr(input, '|'))
	{
		if (!parse_pipes(input_splited))
			return (false);
	}
	if (ft_strchr(input, '<'))
	{
		if (!parse_redin(input_splited))
			return (false);
	}
	if (ft_strchr(input, '>'))
	{
		if (!parse_redout(input_splited))
			return (false);
	}
	return (true);
}
