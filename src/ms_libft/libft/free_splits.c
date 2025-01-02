/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:27:17 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/20 12:30:52 by rde-fari         ###   ########.fr       */
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
	return (0);
}
