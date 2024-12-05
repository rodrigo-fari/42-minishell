/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:29 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/05 17:18:22 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	quote_check(char *input, int i, int s_quote, int d_quote)
{
	char	quote;
	int		validation;

	validation = 0;
	while (input[++i])
	{
		while (input[i] && (input[i] != '\'' && input[i] != '\"'))
			i++;
		quote = input[i++];
		validation++;
		while (input[i] && input[i] != quote)
		{
			if (input[i] == '\"')
				d_quote++;
			if (input[i] == '\'')
				s_quote++;
			i++;
		}
		if (input[i] == quote)
			validation++;
	}
	if (validation % 2 != 0 || s_quote % 2 != 0 || d_quote % 2 != 0)
		return (false);
	return (true);
}

bool	parse_syntax(char **user_input)
{
	if (!user_input)
		return (false);
	return (true);
}
