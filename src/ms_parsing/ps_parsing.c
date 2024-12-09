/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 11:45:12 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parsing(char *input)
{
	char	**user_input;

	validator(parse_quotes(input, -1, 0, 0), "Quotes: ");
	user_input = ft_split(input, ' ');
	validator(parse_pipes(user_input), "Pipes: ");
	validator(parse_redin(user_input), "Redirects in: ");
	validator(parse_redout(user_input), "Redirects out: ");
	validator(parse_heredoc(user_input), "Heredocs: ");
	free_splits(user_input);
}

//comando echo realizado, falta regular.
//estruturar codigo para saber ordens de iniciação.