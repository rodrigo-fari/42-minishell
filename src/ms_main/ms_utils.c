/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:54:38 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/16 16:08:08 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	string_search(const char *s, int c)
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

char	*charjoin(char *str, int c)
{
	char	*ret;
	int		i;

	i = ft_strlen(str);
	ret = malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i++] = (char)c;
	ret[i] = '\0';
	return (ret);
}

int	last_ocurrence(char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (str[i] != (char)c)
		i--;
	return (i);
}
