/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:38:29 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/22 00:30:17 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_export(t_env *env, char **user_input)
{
	int i;
	char **split;

	i = 1;
	if (user_input[1] == NULL)
	{
		print_org_env(env);
		return ;
	}
	while (user_input[i] != NULL)
	{
		split = ft_split(user_input[i], '='); // split[0] = key, split[1] = value
		if (!is_valid_key(split[0]))
			break;
		if (ft_strchr(user_input[i], '=') != NULL)
			env_add(env, split[0], split[1]);

		free_splits(split);
		i++;
	}
}
bool	is_valid_key(char *key)
{
	if (key[0] == '=')
	{
		bi_error("export: not a valid identifier\n");
		return (false);
	}
	if (!ft_isalpha(key[0]) || ft_strchr(key, '-') != NULL)
	{
		bi_error("export: not a valid identifier\n");
		return (false);
	}
	else
		return (true);
}
void	env_add(t_env *env, char *key, char *value)
{
	t_env *new;

	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	listadd_back(&env, new);
}
void	print_org_env(t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp != NULL)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}
