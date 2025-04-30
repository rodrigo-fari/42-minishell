/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:34:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/30 22:20:15 by rde-fari         ###   ########.fr       */
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
		if (!input[i])
			break;
		count++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
		}
		else if (is_special_char(input[i]))
			i++;
		else
		{
			while (input[i] && !ft_isspace(input[i]) && !is_special_char(input[i]))
				i++;
		}
	}
	return (count);
}

char	**tk_splitter(char *input, int i, int j)
{
	char	**commands;
	int	 word_count;

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

int is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '&'
			|| c == ';');
}

char	*extract_word(char *input, int *i)
{
	char	quote;
	int	 cursor;
	int	 start;
	char	*word;

	cursor = *i;
	start = *i;
	if (is_special_char(input[cursor]))
	{
		if (input[cursor] == '>' && input[cursor + 1] == '>')
		{
			word = ft_substr(input, cursor, 2);
			cursor += 2;
		}
		else if (input[cursor] == '<' && input[cursor + 1] == '<')
		{
			word = ft_substr(input, cursor, 2);
			cursor += 2;
		}
		else
		{
			word = ft_substr(input, cursor, 1);
			cursor++;
		}
		*i = cursor;
		return (word);
	}
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
		else if (is_special_char(input[cursor]))
			break;
		else
			cursor++;
	}
	word = ft_substr(input, start, cursor - start);
		if (!word)
			return (NULL);
	*i = cursor;
	return (word);
}
