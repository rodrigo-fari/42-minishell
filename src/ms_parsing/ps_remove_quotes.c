/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:13:33 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/11 17:14:09 by rde-fari         ###   ########.fr       */
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

	second_quote = (first_quote == '\'') ? '\"' : '\'';
	output = malloc(ft_strlen(input) + 1);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == second_quote || (input[i] != '\'' && input[i] != '\"'))
			output[j++] = input[i];
		i++;
	}
	output[j] = '\0';
	free(input);
	return (output);
}

void	remove_quotes(char **commands)
{
	int		i;
	int		single_quotes;
	int		double_quotes;
	char	first_quote;

	i = 0;
	while (commands[i])
	{
		single_quotes = count_quotes(commands[i], '\'');
		double_quotes = count_quotes(commands[i], '\"');
		if (has_only_one_kind_of_quote(commands[i]))
			commands[i] = extract_argument(commands[i]);
		else if (single_quotes > 0 && double_quotes > 0)
		{
			first_quote = '\0';
			//!REMOVER FOR (POSSIVELMENTE CRIAR FUNÇÃO AUXILIAR)================
			for (int k = 0; commands[i][k]; k++)
			{
				if (commands[i][k] == '\'' || commands[i][k] == '\"')
				{
					first_quote = commands[i][k];
					break;
				}
			}
			//!FOR END =========================================================
			int first_quote_count = 0;
			//!REMOVER FOR (POSSIVELMENTE CRIAR FUNÇÃO AUXILIAR)================
			for (int k = 0; commands[i][k]; k++)
			{
				if (commands[i][k] == first_quote)
					first_quote_count++;
				else if (commands[i][k] != '\'' && commands[i][k] != '\"')
					break;
			}
			//!FOR END =========================================================
			if (first_quote_count % 2 == 0)
				commands[i] = extract_argument(commands[i]);
			else
			{
				commands[i] = extract_second_quote_and_argument(commands[i], first_quote);
			}
		}
		i++;
	}
}
