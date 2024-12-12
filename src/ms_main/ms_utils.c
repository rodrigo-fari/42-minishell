/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:54:38 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/12 10:33:49 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	string_search	(const char *s, int c)
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

char	**list_to_array(t_env *env)
{
	char	**arr_env;
	int		size;
	int		i;

	size = listsize(env);
	arr_env = malloc(sizeof(char *) * (size + 1));
	if (!arr_env)
		return (NULL);
	i = 0;
	while (i <= size)
		arr_env[i++] = NULL;
	i = 0;
	while (env)
	{
		arr_env[i] = ft_strjoin(env->key, "=");
		arr_env[i] = ft_strjoin(arr_env[i], env->value);
		env = env->next;
		i++;
	}
	arr_env[i] = NULL;
	return (arr_env);
}

//aloca memoria pro arr** do damanho da lista + 1 (NULL)
//poe a key na string
//poe o "="
//poe o value na string
//poe o nulo n string
//aloca memoria do tamanho da string no array
//poe a string dentro do array[i]
//free da string
//env = env->next