/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftt_strnstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:16:27 by rde-fari          #+#    #+#             */
/*   Updated: 2024/11/30 16:24:39 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ftt_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lenbig;
	size_t	lenlil;

	lenbig = ft_strlen(big);
	lenlil = ft_strlen(little);
	if (lenbig < lenlil)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j] && j < len)
		{
			while (little[j] != '\0')
			{
				i++;
				j++;
			}
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/* 
int main()
{
	const char	big="Rodrigo de Faria Falcao Santos";
	const char	little="cao Sa";
	size_t len = 30;
	ft_strnstr(big, little, len);
	return (0);
} */