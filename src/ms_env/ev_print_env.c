/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:18:36 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/18 11:35:28 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env	*temp;

	env = env_manager(NULL);
	temp = env;
	while (temp)
	{
		if (temp->value && temp->value[0] != '\0')
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
