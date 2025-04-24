/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char_to_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:22:44 by rde-fari          #+#    #+#             */
/*   Updated: 2025/04/24 01:48:16 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*append_char_to_string(char *str, char c)
{
    char	*new_str;
    size_t	len = str ? ft_strlen(str) : 0;

    new_str = malloc(len + 2);
    if (!new_str)
        return (NULL);
    if (str)
        ft_strcpy(new_str, str);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return (new_str);
}
