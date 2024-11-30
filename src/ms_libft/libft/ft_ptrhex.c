/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:55:50 by rde-fari          #+#    #+#             */
/*   Updated: 2024/07/27 15:11:13 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ptrhex(char format, unsigned long num, int *total)
{
	if (format == 'p' && num == 0)
	{
		ft_strncount("(nil)", total);
		return ;
	}
	ft_strncount("0x", total);
	ft_hexapplier(format, num, total);
}
