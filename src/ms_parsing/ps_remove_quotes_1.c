/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:13:33 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/12 18:15:25 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *input, char quote)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == quote)
			count++;
		i++;
	}
	return (count);
}

int	has_only_one_kind_of_quote(char *input)
{
	int	has_single_quote;
	int	has_double_quote;

	has_single_quote = count_quotes(input, '\'') > 0;
	has_double_quote = count_quotes(input, '\"') > 0;
	return (has_single_quote != has_double_quote);
}

char	*extract_argument(char *input)
{
	int		i;
	int		j;
	char	*output;

	output = malloc(ft_strlen(input) + 1);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != '\'' && input[i] != '\"')
			output[j++] = input[i];
		i++;
	}
	output[j] = '\0';
	free(input);
	return (output);
}

char	*extract_second_quote_and_argument(char *input, char first_quote)
{
	int		i;
	int		j;
	char	*output;
	char	second_quote;

	if (first_quote == '\'')
		second_quote = '"';
	else
		second_quote = '\'';
	output = malloc(ft_strlen(input) + 1);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == second_quote || (input[i] != '\'' && input[i] != '"'))
			output[j++] = input[i];
		i++;
	}
	output[j] = '\0';
	free(input);
	return (output);
}
