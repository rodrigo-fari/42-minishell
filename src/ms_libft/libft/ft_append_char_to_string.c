/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char_to_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:22:44 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/25 11:22:53 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*append_char_to_string(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (str == NULL)
		len = 0;
	else
		len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (str != NULL)
		ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
