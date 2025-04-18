/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expand_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:13:03 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/18 16:35:58 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_in_single_quotes(const char *str, int pos)
{
	bool	in_quotes = false;
	int		i = 0;

	while (i < pos)
	{
		if (str[i] == '\'')
			in_quotes = !in_quotes;
		i++;
	}
	return (in_quotes);
}

static char	*expand_exit_code(const char *value, int pos)
{
	char	*itoa_str;
	char	*before;
	char	*after;
	char	*result;

	itoa_str = ft_itoa(g_exit_status);
	before = ft_substr(value, 0, pos);
	after = ft_strdup(value + pos + 2);
	result = ft_strjoin(before, itoa_str);
	free(before);
	before = ft_strjoin(result, after);
	free(result);
	free(after);
	free(itoa_str);
	return (before);
}

static char	*process_token_value(const char *value)
{
	char	*result;
	int		i;

	result = ft_strdup(value);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1] == '?' && !is_in_single_quotes(result, i))
		{
			char *temp = result;
			result = expand_exit_code(result, i);
			free(temp);
			i += ft_strlen(ft_itoa(g_exit_status)) - 1; // Skip expanded length
		}
		else
			i++;
	}
	return (result);
}

void	expand_exit(t_token *tokens)
{
	t_token	*current;
	char	*temp;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_ENV_VAR) // Apenas processa tokens do tipo WORD
		{
			temp = current->value;
			current->value = process_token_value(current->value);
			free(temp);
		}
		current = current->next;
	}
}
