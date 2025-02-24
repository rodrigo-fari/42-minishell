/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_var_expand_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:27:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/24 16:41:58 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *append_char_to_str(char *str, char c)
{
	size_t len = strlen(str);
	char *new_str = realloc(str, len + 2);
	if (!new_str)
		return NULL;
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return new_str;
}

char *expand_variables(char *str)
{
	char *result;
	char *start;
	char *end;
	char *var_value;
	size_t old_size;
	bool in_single_quotes;

	result = malloc(1);
	if (!result)
		return NULL;
	result[0] = '\0';
	start = str;
	in_single_quotes = false;
	while (*start)
	{
		if (*start == '\'')
			in_single_quotes = !in_single_quotes;
		if (!in_single_quotes && (end = ft_strchr(start, '$')))
		{
			old_size = ft_strlen(result);
			result = process_segment(result, &start, end);
			var_value = replace_variable(start, &start);
			if (var_value)
			{
				result = ft_realloc(result, old_size + ft_strlen(var_value) + 1);
				if (!result)
					return NULL;
				ft_strcat(result, var_value);
				free(var_value);
			}
		}
		else
		{
			result = append_char_to_str(result, *start);
			start++;
		}
	}
	return result;
}

void replace_env_variables(char **commands)
{
	int i;
	char *result;

	i = 0;
	while (commands[i])
	{
		result = expand_variables(commands[i]);
		free(commands[i]);
		commands[i] = result;
		i++;
	}
}