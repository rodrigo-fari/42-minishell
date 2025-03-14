/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2025/01/02 11:38:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/23 14:11:45 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// split[0] = key, split[1] = value
void	bi_export(t_env *env, char **user_input)
{
	int		i;
	char	**split;
	bool	has_equal;

	i = 1;
	if (user_input[1] == NULL)
	{
		print_org_env(env);
		return ;
	}
	while (user_input[i] != NULL)
	{
		split = ft_split(user_input[i], '=');
		has_equal = (ft_strchr(user_input[i], '=') != NULL);
		if (!is_valid_key(split[0]))
			break ;
		if (has_equal)
			env_update(env, split[0], split[1], true);
		else
			env_update(env, split[0], "", false);
		free_splits(split);
		i++;
	}
}

bool	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (key[0] == '=')
	{
		ms_print_fd("export: not a valid identifier\n", 2);
		return (false);
	}
	if (!ft_isalpha(key[0]) || ft_strchr(key, '-') != NULL)
	{
		ms_print_fd("export: not a valid identifier\n", 2);
		return (false);
	}
	while (key[i] != '\0' && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ms_print_fd("export: not a valid identifier\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

void	env_add(t_env *env, char *key, char *value, bool has_equal)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->has_equal = has_equal;
	new->next = NULL;
	listadd_back(&env, new);
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
