/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:18:19 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/26 22:28:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_quotes(char *input)
{
	char	quote;
	int		validation;
	int		i;

	i = -1;
	validation = 0;
	while (input[++i])
	{
		while (input[i] && (input[i] != '\'' && input[i] != '\"'))
			i++;
		quote = input[i++];
		validation++;
		while (input[i] && input[i] != quote)
			i++;
		if (input[i] == quote)
			validation++;
		if (!input[i])
			break ;
	}
	if (validation % 2 != 0)
	{
		ps_error("bash: syntax error near unexpected token: \" || \' ");
		return (false);
	}
	return (true);
}
