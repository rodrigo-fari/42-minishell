/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:47:45 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/13 17:48:06 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//*Se a comparação do input com as envs existir, função já retorna um strdup do valor da variavel (já expandida).

char *env_compare(char *input)
{
	t_env *temp = env_manager(NULL);
	while (temp)
	{
		if (ft_strcmp(temp->key, input) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return NULL;
}

void	replace_env_variables(char **commands) {
	for (int i = 0; commands[i] != NULL; i++) {
		char *str = commands[i];
		char *result = malloc(1);
		result[0] = '\0';
		char *start = str;
		char *end;
		while ((end = strchr(start, '$')) != NULL) {
			char *temp = strndup(start, end - start);
			result = realloc(result, strlen(result) + strlen(temp) + 1);
			strcat(result, temp);
			free(temp);
			start = end + 1;
			char *var_end = start;
			while (*var_end && (isalnum(*var_end) || *var_end == '_')) {
				var_end++;
			}
			char *var_name = strndup(start, var_end - start);
			char *var_value = env_compare(var_name);
			if (var_value) {
				result = realloc(result, strlen(result) + strlen(var_value) + 1);
				strcat(result, var_value);
				free(var_value);
			} else {
				result = realloc(result, strlen(result) + strlen(var_name) + 2);
				strcat(result, "$");
				strcat(result, var_name);
			}
			free(var_name);
			start = var_end;
		}
		if (*start) {
			result = realloc(result, strlen(result) + strlen(start) + 1);
			strcat(result, start);
		}
		free(commands[i]);
		commands[i] = result;
	}
}
