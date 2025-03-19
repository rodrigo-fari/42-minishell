/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:07 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/19 16:04:44 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_fix(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		commands[i] = verify_quotes(commands[i]);
		i++;
	}
}

char	*verify_quotes(char *input)
{
	int		i;
	char	current_quote;
	bool	key;

	key = false;
	i = 0;
	current_quote = '\0';
	if (input[i] && (input[i] == '\"' || input[i] == '\''))
		current_quote = input[i];
	while (input[i] == current_quote)
	{
		key = bool_changer(key);
		i++;
	}
	return (replace_values(input, i, current_quote, key));
}

char	*replace_values(char *input, int i, char current_quote, bool key)
{
	char	*ret_str;

	if (key == true && current_quote == '\"')
	{
		ret_str = remove_quotes_and_expand(input, i, current_quote);
		free(input);
		return (ret_str);
	}
	else if (key == true && current_quote == '\'')
	{
		ret_str = remove_quotes_and_expand(input, i, current_quote);
		free(input);
		return (ret_str);
	}
	//else
	ret_str = remove_quotes(input);
	free(input);
	return (ret_str);
}

char	*remove_quotes_and_expand(char *input, int start, char current_quote)
{
	char	*ret_str;
	char	*tmp;
	int		i;

	i = start;
	ret_str = NULL;
	while (input[i] && input[i] != current_quote)
	{
		tmp = append_char_to_string(ret_str, input[i]);
		ret_str = tmp;
		i++;
	}
	return (ret_str);
}

char	*remove_quotes(char *input)
{
	char	*ret_str;
	char	*tmp;
	int		i;

	i = 0;
	ret_str = NULL;
	while (input[i] && (input[i] == '\"' || input[i] == '\''))
		i++;
	while (input[i] && input[i] != '\"' && input[i] != '\'')
	{
		tmp = append_char_to_string(ret_str, input[i]);
		ret_str = tmp;
		i++;
	}
	return (ret_str);
}
