/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:38:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/01/02 11:38:39 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_export(t_env *env, char **user_input)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (user_input[i])
	{
		if (ft_strchr(user_input[i], '='))
		{
			key = ft_substr(user_input[i], 0,
					ft_strchr(user_input[i], '=') - user_input[i]);
			value = ft_strdup(ft_strchr(user_input[i], '=') + 1);
			if (env_add(env, key, value) == false)
			{
				free(key);
				free(value);
			}
		}
		else
			env_add(env, user_input[i], "");
		i++;
	}
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
