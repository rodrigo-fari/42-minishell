/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expand_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:48:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/24 15:17:16 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	replace_exit_status(char **commands, int i)
{
	char	*expanded_str;
	char	*remaining_str;
	char	*pos;

	pos = ft_strnstr(commands[i], "$?", ft_strlen(commands[i]));
	while (pos)
	{
		expanded_str = ft_strjoin(ft_substr(commands[i], 0, pos - commands[i]), ft_itoa(g_exit_status));
		remaining_str = ft_strdup(pos + 2);
		free(commands[i]);
		commands[i] = ft_strjoin(expanded_str, remaining_str);
		free(expanded_str);
		free(remaining_str);
		pos = ft_strnstr(commands[i], "$?", ft_strlen(commands[i]));
	}
}

void	expand_exit(char **commands)
{
	int		i;
	int		j;
	int		quotes;

	i = 0;
	while (commands[i])
	{
		quotes = 0;
		j = 0;
		while (commands[i][j])
		{
			if (commands[i][j] == '"')
				quotes = !quotes;
			if (!quotes)
				replace_exit_status(commands, i);  // Substitui "$?" fora das aspas
			j++;
		}
		i++;
	}
}

