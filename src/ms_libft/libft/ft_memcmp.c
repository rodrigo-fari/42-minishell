/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:30:33 by rde-fari          #+#    #+#             */
/*   Updated: 2024/04/22 12:37:11 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*v1;
	const char	*v2;
	size_t		i;

	v1 = s1;
	v2 = s2;
	i = 0;
	while (i < n)
	{
		if (v1[i] == v2[i])
			i++;
		else
			return ((unsigned char)v1[i] - (unsigned char)v2[i]);
	}
	return (0);
}
