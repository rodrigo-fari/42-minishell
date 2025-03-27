/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipeline_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:15:23 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/27 19:16:06 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipeline(char ***pipeline)
{
	int	i;

	i = 0;
	while (pipeline[i])
	{
		free(pipeline[i]);
		i++;
	}
	free(pipeline);
}
