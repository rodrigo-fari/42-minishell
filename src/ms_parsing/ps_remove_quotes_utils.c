/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_remove_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:14:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/19 14:21:47 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bool_changer(bool key)
{
	return (!key);
}

char	*append_char_to_string(char* str, char c)
{
	char	*new_str;
	size_t	len;

	if (str == NULL)
		len = 0;
	else
		len = ft_strlen(str);
	new_str = (char*)malloc(len + 2);
	if (new_str == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	if (str != NULL)
		strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return new_str;
}
