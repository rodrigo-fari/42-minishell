/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:22 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/18 13:34:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char *str, char c)
{
	char	*result;
	int		len;

	len = 0;
	if (str)
		len = strlen(str);
	result = (char *)malloc((len + 2) * sizeof(char));
	if (!result)
		return (NULL);
	if (str)
		ft_strcpy(result, str);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}
