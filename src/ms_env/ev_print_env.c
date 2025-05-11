/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:18:36 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/11 19:52:19 by rde-fari         ###   ########.fr       */
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
		printf("%s", temp->key);
		printf("=");
		if (temp->value)
			printf("%s", temp->value);
		printf("\n");
		temp = temp->next;
	}
}
