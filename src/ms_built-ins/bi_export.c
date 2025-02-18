/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:38:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/18 12:03:11 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_org_env(t_env *env);
void org_env(t_env *env);
void add_sorted(t_env **sorted, t_env *new_node);

void	bi_export(t_env *env, char **user_input)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (!user_input[i])
	{
		org_env(env);
		return ;
	}
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
void add_sorted(t_env **sorted, t_env *new_node)
{
	t_env *tmp;
	t_env *tmp2;

	tmp = *sorted;
	tmp2 = NULL;
	while (tmp && ft_strcmp(tmp->key, new_node->key) < 0)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp2)
		tmp2->next = new_node;
	else
		*sorted = new_node;
	new_node->next = tmp;
}

void org_env(t_env *env)
{
	t_env *temp;
	t_env *sorted;
	t_env *new_node;

	sorted = NULL;
	temp = env;
	while (temp)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return;
		new_node->key = ft_strdup(temp->key);
		new_node->value = ft_strdup(temp->value);
		new_node->next = NULL;
		add_sorted(&sorted, new_node);
		temp = temp->next;
	}
	print_org_env(sorted);
}

void print_org_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->value && temp->value[0] != '\0')
			printf("declare -x %s=%s\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}
