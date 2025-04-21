/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:07:21 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/21 22:16:01 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_space_sign(char **str, int *sign)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

static void	ft_parse_number(char *str, double *r, double *f)
{
	double	div;
	bool	dec;

	div = 10.0;
	dec = false;
	while ((*str >= '0' && *str <= '9') || (*str == '.' && !dec))
	{
		if (*str == '.')
			dec = true;
		else if (!dec)
			*r = *r * 10.0 + (*str - '0');
		else
		{
			*f += (*str - '0') / div;
			div *= 10.0;
		}
		str++;
	}
}

double	ft_atod(char *str)
{
	double	result;
	double	frac;
	int		sign;

	result = 0.0;
	frac = 0.0;
	sign = 1;
	ft_skip_space_sign(&str, &sign);
	ft_parse_number(str, &result, &frac);
	return ((result + frac) * sign);
}
