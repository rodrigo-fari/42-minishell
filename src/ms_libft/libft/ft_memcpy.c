/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:36:35 by rde-fari          #+#    #+#             */
/*   Updated: 2024/04/18 17:02:08 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*destiny;

	source = (unsigned char *)src;
	destiny = dest;
	i = 0;
	while ((source || destiny) && (i < n))
	{
		destiny[i] = source[i];
		i++;
	}
	return (destiny);
}
