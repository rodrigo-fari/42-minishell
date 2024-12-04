/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:52:03 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/04 21:08:54 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parsing(char *input)
{
	char **user_input;

	check_quotes(input); // verifica as aspas antes de splitar para ver a syntax dos tokens.
	user_input = ft_split(input, ' ');
	parse_syntax(user_input);
	free_splits(user_input);
}
