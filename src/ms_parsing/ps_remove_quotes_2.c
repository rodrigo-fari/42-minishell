/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:59:27 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/12 18:17:50 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	find_first_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (str[i]);
		i++;
	}
	return ('\0');
}

int	count_first_quote(char *str, char quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == quote)
			count++;
		else if (str[i] != '\'' && str[i] != '"')
			break ;
		i++;
	}
	return (count);
}

void	remove_quotes(char **commands)
{
	int		i;
	int		single_quotes;
	int		double_quotes;
	char	first_quote;
	int		first_quote_count;

	i = 0;
	while (commands[i])
	{
		single_quotes = count_quotes(commands[i], '\'');
		double_quotes = count_quotes(commands[i], '"');
		if (has_only_one_kind_of_quote(commands[i]))
			commands[i] = extract_argument(commands[i]);
		else if (single_quotes > 0 && double_quotes > 0)
		{
			first_quote = find_first_quote(commands[i]);
			first_quote_count = count_first_quote(commands[i], first_quote);
			if (first_quote_count % 2 == 0)
				commands[i] = extract_argument(commands[i]);
			else
				commands[i] = extract_second_quote_and_argument(commands[i],
						first_quote);
		}
		i++;
	}
}
