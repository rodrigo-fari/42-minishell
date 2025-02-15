/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_var_expand_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:47:45 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/15 18:40:38 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_compare(char *input)
{
	t_env	*temp;

	temp = env_manager(NULL);
	while (temp)
	{
		if (ft_strcmp(temp->key, input) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

char	*append_str(char *result, char *str)
{
	char	*new_result;

	new_result = ft_realloc(result, ft_strlen(result) + ft_strlen(str) + 1);
	if (!new_result)
		return (NULL);
	ft_strcat(new_result, str);
	return (new_result);
}

char	*extract_variable(char *start, char **new_start)
{
	char	*var_end;
	char	*var_name;

	var_end = start;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	var_name = ft_strndup(start, var_end - start);
	*new_start = var_end;
	return (var_name);
}

char	*replace_variable(char *start, char **new_start)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_variable(start, new_start);
	var_value = env_compare(var_name);
	free(var_name);
	return (var_value);
}

char	*process_segment(char *result, char **start, char *end)
{
	char	*temp;

	temp = ft_strndup(*start, end - *start);
	result = append_str(result, temp);
	free(temp);
	*start = end + 1;
	return (result);
}
