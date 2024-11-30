/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:32:30 by rde-fari          #+#    #+#             */
/*   Updated: 2024/04/24 18:03:45 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int num)
{
	int	value;

	if (num == 0)
		return (1);
	value = 0;
	if (num < 0)
	{
		value += 1;
		num *= (-1);
	}
	while (num != 0)
	{
		num = num / 10;
		value++;
	}
	return (value);
}

char	*is_negative(char *str, int n, int malloc_size)
{
	n *= (-1);
	str[0] = '-';
	while (malloc_size > 1)
	{
		malloc_size--;
		str[malloc_size] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	malloc_size;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	malloc_size = ft_intlen(n);
	str = malloc(sizeof(char) * (malloc_size + 1));
	if (!str)
		return (NULL);
	str[malloc_size] = '\0';
	if (n < 0)
		str = is_negative(str, n, malloc_size);
	else
	{
		while (malloc_size > 0)
		{
			str[malloc_size - 1] = (n % 10) + 48;
			n /= 10;
			malloc_size--;
		}
	}
	return (str);
}
