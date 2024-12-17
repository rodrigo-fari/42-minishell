/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:39:28 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/17 11:38:02 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_env *head)
{
	t_env	*temp;

	temp = env_manager(head);
	while (temp->next)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	listadd_back(t_env **lst, t_env *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		list_last(*lst)->next = new;
}

t_env	*list_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	free_env_struct(t_env *env)
{
	while (env->next)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		env = env->next;
	}
	free(env);
	env = NULL;
}

int	listsize(t_env *env)
{
	size_t	size;

	if (env == NULL)
		return (0);
	size = 1;
	while (env->next != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}
