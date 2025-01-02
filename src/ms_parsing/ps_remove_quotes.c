/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:57:40 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/28 16:57:01 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **commands)
{
	char	quote;
	int		i;

	i = 0;
	while (commands[i])
	{
		if (commands[i][0] == '\'' || commands[i][0] == '\"')
			quote = commands[i][0];
		if (first_quote_number(commands[i]) % 2 == 0)
			commands[i] = remove_quote_even(commands[i]);
		else
			commands[i] = remove_quote_odd(commands[i], quote);
		i++;
	}
}

char	*remove_quote_odd(char *input, char first_quote)
{
	char	*n_input;
	int		size;
	int		i;
	int		j;

	size = (ft_strlen(input)) - (first_quote_number(input) * 2);
	n_input = ft_calloc(sizeof(char), (size + 1));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] && input[i] == first_quote)
			i++;
		else
			n_input[j++] = input[i++];
	}
	n_input[j] = '\0';
	free(input);
	return (n_input);
}

char	*remove_quote_even(char *input)
{
	char	*n_input;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(input) - total_quotes(input);
	n_input = ft_calloc(sizeof(char), (size + 1));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] && (input[i] == '\"' || input[i] == '\''))
			i++;
		else
			n_input[j++] = input[i++];
	}
	free(input);
	return (n_input);
}

int	total_quotes(char *input)
{
	int	total_quotes;
	int	i;

	i = 0;
	total_quotes = 0;
	while (input [i])
	{
		if (input[i] && (input[i] == '\"' || input[i] == '\''))
		{
			total_quotes++;
			i++;
		}
		else
			i++;
	}
	return (total_quotes);
}

int	first_quote_number(char *input)
{
	int		quote_count;
	char	first_quote;
	int		i;

	quote_count = 0;
	first_quote = 0;
	i = 0;
	while (input[i])
	{
		if (!first_quote && (input[i] == '\'' || input[i] == '\"'))
			first_quote = input[i];
		if (input[i] == first_quote)
			quote_count++;
		i++;
	}
	return (quote_count / 2);
}
