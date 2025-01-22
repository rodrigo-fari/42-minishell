/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:57:40 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/22 12:24:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **commands)
{
	int	i;
	int	j;
	int	quote_nbr;

	quote_nbr = 0;
	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			if (commands[i][j] == '\"' || commands[i][j] == '\'')
				quote_nbr++;
			j++;
		}
		if (quote_nbr % 2 == 0)
			commands[i] = remove_all_quotes(commands[i]);
		else
			if (quote_type(commands[i]) == 2)
				remove_all_quotes(commands[i]);
			else
				remove_first_quote(commands[i]);
		i++;
	}
}

int	quote_nbr(char *input)
{
	int		i;
	int		quotes;

	quotes = 0;
	i = 0;

	while (input[i])
	{
		if (input [i] == '\'' || input[i] == '\"')
			quotes++;
		i++;
	}
	return (quotes);
}

int	quote_type(char *input)
{
	int		i;
	char	quote;
	int		quote_nbr;

	quote_nbr = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote = input[i++];
			quote_nbr++;
		}
		if (input[i] == quote)
			quote_nbr++;
		i++;
	}
	return (quote_nbr);
}

char	*remove_all_quotes(char *input)
{
	int		i;
	int		j;
	int		size;
	char	*output;

	size = ft_strlen(input) - quote_nbr(input);
	output = ft_calloc(sizeof(char), (size + 1));
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input [i] == '\'')
			i++;
		else
			output[j++] = input[i++];
	}
	output[j] = '\0';
	free (input);
	return (output);
}


char	*remove_first_quote(char *input)
{
	int		i;
	int		j;
	int		size;
	char	quote;
	char	*output;

	i = 0;
	while (input[i] && (input[i] != '\'' || input [i] != '\"'))
		i++;
	if (input[i] && (input[i] != '\'' || input [i] != '\"'))
		quote = input[i];
	i = 0;
	while (input[i])
	{
		while (input[i] == quote)
			i++;
		size++;
		i++;
	}
	output = ft_calloc(sizeof(char), (size + 1));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] && input[i] == quote)
			i++;
		else
			output[j] = input[i];
	}
	free (input);
	return (output);
}
