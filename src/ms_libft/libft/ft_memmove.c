/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:05:51 by rde-fari          #+#    #+#             */
/*   Updated: 2024/04/18 18:21:31 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destiny;
	unsigned char	*source;

	source = (unsigned char *)src;
	destiny = dest;
	if (source > destiny)
	{
		ft_memcpy(destiny, source, n);
	}
	if (destiny > source)
	{
		while (n > 0)
		{
			destiny[n - 1] = source[n - 1];
			n--;
		}
	}
	return (dest);
}
