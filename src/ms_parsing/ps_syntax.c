/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:29 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/05 19:50:43 by rde-fari         ###   ########.fr       */
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

bool	parse_pipes(char **user_input)
{
	int	i;

	if (user_input[0][0] == '|')
		return (false);
	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '|')
		{
			if (user_input[i + 1] && !ft_isalnum(user_input[i - 1][0]))
				return (false);
			if (!user_input[i + 1] || !ft_isalnum(user_input[i + 1][0]))
				return (false);
		}
		i++;
	}
	return (true);
}
