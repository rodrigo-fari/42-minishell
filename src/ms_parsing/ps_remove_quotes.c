/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:07 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/18 13:59:24 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_fix(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		verify_quotes(commands[i]);
		i++;
	}
}

void	verify_quotes(char *input)
{
	int		i;
	char	*ret_str;
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
	if (key == true && current_quote == '\"')
		ret_str = remove_quotes_and_expand(input, i, current_quote);
}

char	*remove_quotes_and_expand(char *input, int start, char current_quote)
{
	char	*tmp;
	int		i;

	i = start;
	while (input[i] && input[i] != current_quote)
	{
		i++;
		//falte resolver o que isto vai fazer. ultilizar o charjopin da core dumpppp :p
	}
	return (tmp);
}

// char	*remove_quotes(char *input)
// {
	
// }
