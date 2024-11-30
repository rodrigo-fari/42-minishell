/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:41:26 by rde-fari          #+#    #+#             */
/*   Updated: 2024/05/01 20:41:59 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cw(const char	*str, char c)
{
	size_t	i;
	size_t	cw;

	i = 0;
	cw = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			cw++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cw);
}

char	**splitter(char const *s, char c, char **result)
{
	size_t	i;
	size_t	j;
	size_t	limit;
	size_t	start;

	j = 0;
	i = 0;
	limit = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i])
		{
			i++;
			limit++;
		}
		result[j++] = ft_substr(s, start, limit);
		limit = 0;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), (cw(s, c) + 1));
	if (!result)
		return (NULL);
	result = splitter(s, c, result);
	return (result);
}
