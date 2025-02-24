/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expand_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:48:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/24 14:10:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_exit(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], "$?") == 0)
		{
			free(commands[i]);
			commands[i] = ft_strdup(ft_itoa(g_exit_status));
		}
		i++;
	}
}
