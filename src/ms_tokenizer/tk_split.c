/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:34:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/14 22:03:07 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

int	tk_count_words(char *input, int i, int count)
{
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		count++;
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, i);
		else if (is_special_char(input[i]))
			i++;
		else
		{
			while (input[i]
				&& !ft_isspace(input[i])
				&& !is_special_char(input[i]))
				i++;
		}
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
		{
			free_splits(commands);
			return (NULL);
		}
		j++;
	}
	commands[j] = NULL;
	return (commands);
}

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '&'
		|| c == ';' || c == '|');
}

char	*extract_special_token(char *input, int *i)
{
	char	*word;

	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		word = ft_substr(input, *i, 2);
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		word = ft_substr(input, *i, 2);
		*i += 2;
	}
	else
	{
		word = ft_substr(input, *i, 1);
		*i += 1;
	}
	return (word);
}
