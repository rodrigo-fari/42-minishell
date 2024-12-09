/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 15:10:43 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parsing(char *input)
{
	char	**user_input;

	if (!parse_quotes(input, -1, 0, 0))
		ps_error("Invalid syntax: \"/\' ", NULL);
	user_input = ft_split(input, ' ');
	if (!parse_pipes(user_input))
		ps_error("Invalid syntax: | ", user_input);
	else if (!parse_heredoc(user_input))
		ps_error("Invalid syntax: << ", user_input);
	else if (!parse_redin(user_input))
		ps_error("Invalid Syntax: < ", user_input);
	else if (!parse_redout(user_input))
		ps_error("Invalid syntax: >/>> ", user_input);
	else
		free_splits(user_input);
	return (true);
}

//comando echo realizado, falta regular.
//estruturar codigo para saber ordens de iniciação.