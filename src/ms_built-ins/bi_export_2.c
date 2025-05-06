/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:16:30 by aeberius          #+#    #+#             */
/*   Updated: 2025/05/06 20:39:13 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	org_env_alpha(t_env *env)
{
	t_env	*temp;
	t_env	*temp2;
	char	*key;
	char	*value;

	temp = env;
	while (temp != NULL)
	{
		temp2 = temp->next;
		while (temp2 != NULL)
		{
			if (ft_strcmp(temp->key, temp2->key) > 0)
			{
				key = temp->key;
				value = temp->value;
				temp->key = temp2->key;
				temp->value = temp2->value;
				temp2->key = key;
				temp2->value = value;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

void	print_org_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	org_env_alpha(env);
	while (temp != NULL)
	{
		if (temp->has_equal)
		{
			if (temp->value)
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("declare -x %s=\"\"\n", temp->key);
		}
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

void	env_update(t_env *env, char *key, char *value, bool has_equal)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			temp->has_equal = has_equal;
			return ;
		}
		temp = temp->next;
	}
	env_add(env, key, value, has_equal);
}

void	handle_invalid_key(char *key, char *value)
{
	bi_error("Minishell: export: not a valid identifier\n");
	free(key);
	free(value);
	g_exit_status = 1;
}
