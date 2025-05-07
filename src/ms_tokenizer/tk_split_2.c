/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:30:14 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/07 18:37:51 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quoted_segment(char *input, int cursor)
{
	char	quote;

	quote = input[cursor++];
	while (input[cursor] && input[cursor] != quote)
		cursor++;
	if (input[cursor] == quote)
		cursor++;
	return (cursor);
}

char	*extract_word(char *input, int *i)
{
	int		cursor;
	int		start;
	char	*word;

	cursor = *i;
	start = *i;
	if (is_special_char(input[cursor]))
		return (extract_special_token(input, i));
	while (input[cursor] && !ft_isspace(input[cursor]))
	{
		if (input[cursor] == '\'' || input[cursor] == '\"')
			cursor = skip_quoted_segment(input, cursor);
		else if (is_special_char(input[cursor]))
			break ;
		else
			cursor++;
	}
	word = ft_substr(input, start, cursor - start);
	if (!word)
		return (NULL);
	*i = cursor;
	return (word);
}
