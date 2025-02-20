/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:03 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/20 17:00:48 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	org_env(t_env *env)
{
	t_env	*temp;
	t_env	*sorted;
	t_env	*new_node;

	sorted = NULL;
	temp = env;
	while (temp)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		new_node->key = ft_strdup(temp->key);
		new_node->value = ft_strdup(temp->value);
		new_node->next = NULL;
		add_sorted(&sorted, new_node);
		temp = temp->next;
	}
	print_org_env(sorted);
}

void	print_org_env(t_env *env)
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
