/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:33:24 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/27 19:34:07 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_fix(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		commands[i] = verify_quotes(commands[i]);
		i++;
	}
}
