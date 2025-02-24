/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_var_expand_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:27:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/24 17:13:06 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char_to_str(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = strlen(str);
	new_str = realloc(str, len + 2);
	if (!new_str)
		return (NULL);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*handle_variable_expansion(char *result, char **start, char *end)
{
	size_t	old_size;
	char	*var_value;

	old_size = ft_strlen(result);
	result = process_segment(result, start, end);
	var_value = replace_variable(*start, start);
	if (var_value)
	{
		result = ft_realloc(result, old_size + ft_strlen(var_value) + 1);
		if (!result)
			return (NULL);
		ft_strcat(result, var_value);
		free(var_value);
	}
	return (result);
}

char	*expand_variables_loop(char *result, char *start)
{
	bool	in_single_quotes;
	char	*end;

	in_single_quotes = false;
	while (*start)
	{
		if (*start == '\'')
			in_single_quotes = !in_single_quotes;
		end = ft_strchr(start, '$');
		if (!in_single_quotes && end)
		{
			result = handle_variable_expansion(result, &start, end);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char_to_str(result, *start);
			start++;
		}
	}
	return (result);
}

char	*expand_variables(char *str)
{
	char	*result;

	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	result = expand_variables_loop(result, str);
	return (result);
}

void	replace_env_variables(char **commands)
{
	int		i;
	char	*result;

	i = 0;
	while (commands[i])
	{
		result = expand_variables(commands[i]);
		free(commands[i]);
		commands[i] = result;
		i++;
	}
}
