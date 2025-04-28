/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_env_to_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:13:25 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/28 07:07:27 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_to_struct(char **environ)
{
	t_env	*head;
	t_env	*current;
	char	**key_value;
	int		i;

	head = NULL;
	i = 0;
	while (environ[i])
	{
		key_value = split_once(environ[i], '=');
		if (!key_value)
			return (NULL);
		current = ft_calloc(1, sizeof(t_env));
		if (!current)
			return (NULL);
		current->key = ft_strdup(key_value[0]);
		current->value = ft_strdup(key_value[1]);
		current->has_equal = true;
		current->next = NULL;
		free_splits(key_value);
		listadd_back(&head, current);
		i++;
	}
	env_manager(head);
	return (head);
}

char	**split_once(char *input, char c)
{
	char	**return_array;
	int		i;

	i = 0;
	while (input[i] && input[i] != c)
		i++;
	return_array = malloc(sizeof(char *) * 3);
	if (!return_array)
		return (NULL);
	return_array[0] = ft_substr(input, 0, i);
	if (!input[i])
		return_array[1] = ft_strdup("");
	else
		return_array[1] = ft_strdup(input + i + 1);
	return_array[2] = NULL;
	return (return_array);
}
