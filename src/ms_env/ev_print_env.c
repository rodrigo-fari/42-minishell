/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:18:36 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/26 15:29:18 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env()
{
	t_env	*temp;

	temp = env_manager(NULL);
	while (temp->next)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
