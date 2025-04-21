/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:27:17 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 16:28:11 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_splits(char **line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		free(line[i++]);
	free(line);
	line = NULL;
	return (0);
}
