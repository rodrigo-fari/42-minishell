/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:01:27 by rde-fari          #+#    #+#             */
/*   Updated: 2024/07/27 16:42:48 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncount(char *string, int *total)
{
	int	j;

	j = 0;
	if (string == NULL)
	{
		write(1, "(null)", 6);
		*total += 6;
		return ;
	}
	while (string[j])
	{
		write(1, &string[j], 1);
		*total += 1;
		j++;
	}
}
