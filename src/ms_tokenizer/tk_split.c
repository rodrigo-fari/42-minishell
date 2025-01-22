/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:34:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/22 14:48:59 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tk_count_words(char *input, int i, int count)
{
	char	quote;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i])
		{
			count++;
			if (input[i] == '\'' || input[i] == '\"')
			{
				quote = input[i];
				i++;
				while (input[i] && input[i] != quote)
					i++;
			}
		}
		while (input[i] && !ft_isspace(input[i]))
			i++;
	}
	return (count);
}

char	**tk_splitter(char *input, int i, int j)
{
	char	**commands;
	int		word_count;

	word_count = tk_count_words(input, 0, 0);
	commands = ft_calloc(sizeof(char *), (word_count + 1));
	if (!commands)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		commands[j] = extract_word(input, &i);
		if (!commands[j])
			return (NULL);
		j++;
	}
	commands[j] = NULL;
	return (commands);
}

char	*extract_word(char *input, int *i)
{
	char	quote;
	int		cursor;
	char	*word;

	cursor = *i;
	while (input[cursor] && !ft_isspace(input[cursor]))
	{
		if (input[cursor] == '\'' || input[cursor] == '\"')
		{
			quote = input[cursor++];
			while (input[cursor] && input[cursor] != quote)
				cursor++;
			if (input[cursor] == quote)
				cursor++;
		}
		else
			cursor++;
	}
	word = ft_substr(input, *i, cursor - *i);
	*i = cursor;
	return (word);
}
