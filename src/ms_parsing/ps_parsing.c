/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/16 16:22:51 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parsing(char *input)
{
	char	**input_splited;

	input_splited = ft_split(input, ' ');
	if (!parse_verify_quotes(input_splited, input)
		|| !parse_verify_pipes(input_splited, input)
		|| !parse_verify_redin(input_splited, input)
		|| !parse_verify_redout(input_splited, input))
		return (false);
	free_splits(input_splited);
	return (true);
}

bool	parse_verify_quotes(char **input_splited, char *input)
{
	if (ft_strchr(input, '\"') != 0 || ft_strchr(input, '\'') != 0)
	{
		if (!parse_quotes(input, -1, 0, 0))
		{
			free_splits(input_splited);
			return (false);
		}
	}
	return (true);
}

bool	parse_verify_pipes(char **input_splited, char *input)
{
	if (ft_strchr(input, '|'))
	{
		if (!parse_pipes(input_splited))
		{
			free_splits(input_splited);
			return (false);
		}
	}
	return (true);
}

bool	parse_verify_redin(char **input_splited, char *input)
{
	if (ft_strchr(input, '<'))
	{
		if (!parse_redin(input_splited))
		{
			free_splits(input_splited);
			return (false);
		}
	}
	return (true);
}

bool	parse_verify_redout(char **input_splited, char *input)
{
	if (ft_strchr(input, '>'))
	{
		if (!parse_redout(input_splited))
		{
			free_splits(input_splited);
			return (false);
		}
	}
	return (true);
}
