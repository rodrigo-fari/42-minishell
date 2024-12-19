/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:41:26 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/04 13:04:18 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
	}
	return (i);
}

static size_t	ft_wordlen(char	const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s != c && *s)
	{
		s++;
		i++;
	}
	return (i);
}

static void	ft_clean(char **split, size_t i)
{
	size_t	n;

	n = 0;
	while (n < i)
		free(split[n++]);
	free(split);
}

static char	**ft_splitting(char **split, char const *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			len = ft_wordlen(s, c);
			split[i] = ft_substr(s, 0, len);
			if (!split[i])
			{
				ft_clean(split, i);
				return (NULL);
			}
			s += len;
			i++;
		}
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	*aux;
	char	**split;
	size_t	wc;

	wc = ft_wordcount(s, c);
	aux = ft_calloc(ft_strlen(s), 1);
	if (!aux)
		return (NULL);
	free(aux);
	split = (char **) ft_calloc(wc + 1, 8);
	if (!split)
		return (NULL);
	split = ft_splitting(split, s, c);
	if (!split)
		return (NULL);
	return (split);
}
