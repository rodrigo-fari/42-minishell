/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:54:38 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/11 15:25:44 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	string_seachr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (false);
		i++;
	}
	return (true);
}


//passar da lista para um array:
//aloca memoria pro arr** do damanho da lista + 1 (NULL)
//poe a key na string
//poe o "="
//poe o value na string
//poe o nulo n string
//aloca memoria do tamanho da string no array
//poe a string dentro do array[i]
//free da string
//env = env->next