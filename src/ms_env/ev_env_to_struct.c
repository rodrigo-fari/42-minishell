/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_env_to_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:13:25 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/10 17:44:30 by rde-fari         ###   ########.fr       */
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
		key_value = ft_split(environ[i], '=');
		if (!key_value)
			return (NULL);
		current = ft_calloc(1, sizeof(t_env));
		if (!current)
			return (NULL);
		current->key = ft_strdup(key_value[0]);
		current->value = ft_strdup(key_value[1]);
		current->next = NULL;
		free_splits(key_value);
		listadd_back(&head, current);
		i++;
	}
	env_manager(head);
	return (head);
}
