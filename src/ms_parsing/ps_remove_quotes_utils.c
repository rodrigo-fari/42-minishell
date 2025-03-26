/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:14:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/26 23:21:15 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bool_changer(bool key)
{
	return (!key);
}

char	*extract_var_name(char *input, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = ft_substr(input, start, *i - start);
	return (var_name);
}

char	*get_env_value(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
#include <stdlib.h>
#include <string.h>

char	*append_string_to_string(char *str1, char *str2)
{
	char	*result;
	size_t	len1 = str1 ? strlen(str1) : 0;
	size_t	len2 = str2 ? strlen(str2) : 0;

	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	if (str1)
		strcpy(result, str1);
	if (str2)
		strcpy(result + len1, str2);
	free(str1); // Libera a string original para evitar vazamento de memória
	return (result);
}
