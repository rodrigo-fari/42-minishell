/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 13:24:26 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	parsing(char *input)
{
	char	**user_input;

	parse_quotes(input, -1, 0, 0);
	user_input = ft_split(input, ' ');
	parse_pipes(user_input);
	parse_heredoc(user_input);
	parse_redin(user_input);
	parse_redout(user_input);
	free_splits(user_input);
	return (true);
}

//comando echo realizado, falta regular.
//estruturar codigo para saber ordens de iniciação.