/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:38:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/20 17:18:36 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_key_value(t_env *env, char *user_input)
{
	char	*key;
	char	*value;

	key = ft_substr(user_input, 0, ft_strchr(user_input, '=') - user_input);
	value = ft_strdup(ft_strchr(user_input, '=') + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
	env_add(env, key, value);
	free(key);
	free(value);
}


void	process_user_input(t_env *env, char **user_input)
{
	int	i;

	i = 1;
	while (user_input[i])
	{
		if (ft_strchr(user_input[i], '='))
			add_key_value(env, user_input[i]);
		else
			env_add(env, user_input[i], "");
		i++;
	}
}

void	bi_export(t_env *env, char **user_input)
{
	if (!user_input[1])
	{
		org_env(env);
		return ;
	}
	process_user_input(env, user_input);
}

bool	env_add(t_env *env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (true);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (false);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	listadd_back(&env, new);
	return (true);
}

void	add_sorted(t_env **sorted, t_env *new_node)
{
	t_env *current;

	if (*sorted == NULL || strcmp((*sorted)->key, new_node->key) > 0)
	{
		new_node->next = *sorted;
		*sorted = new_node;
	}
	else
	{
		current = *sorted;
		while (current->next != NULL && strcmp(current->next->key, new_node->key) < 0) {
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}
