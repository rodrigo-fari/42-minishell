/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:01:00 by rde-fari          #+#    #+#             */
/*   Updated: 2024/07/27 15:10:35 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_char(const char *format, va_list ap, int *total)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
				ft_putncount(va_arg(ap, int), total);
			else if (*format == 's')
				ft_strncount(va_arg(ap, char *), total);
			else if (*format == 'd' || *format == 'i' || *format == 'u')
				ft_intncount(ap, *format, total);
			else if (*format == 'x' || *format == 'X')
				ft_hexapplier(*format, va_arg(ap, unsigned int), total);
			else if (*format == 'p')
				ft_ptrhex(*format, va_arg(ap, unsigned long), total);
			else if (*format == '%')
			{
				write(1, "%", 1);
				*total += 1;
			}
		}
		else
			ft_putncount(*format, total);
		format++;
	}
}
