/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_env_to_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:08:32 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/09 11:39:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Converts an environment variables array into a linked list of
 *`t_env` structures.
 *
 * This function takes a `char **environ`, typically provided by the
 * operating system, where each element is a string in the format
 * "KEY=VALUE". It parses the array and converts each entry into a `t_env`
 * node, storing the key and value separately. The nodes are linked into a
 * singly linked list.
 * 
 * @param environ A null-terminated array of strings representing environment
 * variables, formatted as "KEY=VALUE".
 *
 * @return A pointer to the head of the linked list of `t_env` structures.
 *Returns NULL if memory allocation fails or if an error occurs during
 *processing.
 *
 * @note 
 * - The `ft_split` function is used to separate the "KEY" and "VALUE"
 *components of each environment variable string. The format must strictly
 *follow "KEY=VALUE".
 * - The `free_splits` function is called to free the memory allocated by
 *`ft_split`.
 * - Memory is dynamically allocated for each `t_env` node using `malloc`.
 *The caller is responsible for freeing this memory after use.
 * - The `listadd_back` function appends the newly created node to the end of the
 *linked list.
 */
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
		key_value = ft_split(environ[i], '=');
		if (!key_value)
			return (NULL);
		current = malloc(sizeof(t_env));
		if (!current)
			return (NULL);
		current->key = ft_strdup(key_value[0]);
		current->value = ft_strdup(key_value[1]);
		current->next = NULL;
		free_splits(key_value);
		listadd_back(&head, current);
		i++;
	}
	return (head);
}
