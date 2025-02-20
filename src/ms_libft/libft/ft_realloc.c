/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:17:49 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/20 16:17:54 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
    void	*new_ptr;
    size_t	old_size;

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL)
    {
        new_ptr = malloc(new_size);
        if (new_ptr)
            ft_bzero(new_ptr, new_size); // Inicializa a memória alocada
        return (new_ptr);
    }
    old_size = ft_strlen(ptr);
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    ft_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    ft_bzero(new_ptr + old_size, new_size - old_size); // Inicializa a memória adicional
    return (new_ptr);
}