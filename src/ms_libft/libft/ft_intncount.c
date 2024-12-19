/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intncount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:01:08 by rde-fari          #+#    #+#             */
/*   Updated: 2024/07/27 15:10:47 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_intncount(va_list ap, char format, int *total)
{
	int		i;

	i = va_arg(ap, int);
	if (format == 'd' || format == 'i')
	{
		ft_putnbr_fd(i, 1);
		*total += ft_int_len(i);
	}
	else
	{
		ft_unsint(i, total);
	}
}
