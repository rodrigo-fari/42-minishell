/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/07 21:43:38 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parsing(char *input)
{
	char	**user_input;

	validator(quote_check(input, -1, 0, 0), "Quotes: ");
	user_input = ft_split(input, ' ');
	validator(parse_pipes(user_input), "Pipes: ");
	validator(parse_redin(user_input), "Redirects in: ");
	validator(parse_redout(user_input), "Redirects out: ");
	validator(-1, "Heredocs: ");
	free_splits(user_input);
}
