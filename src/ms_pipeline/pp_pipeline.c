/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:14:09 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/12 12:46:57 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char ***split_by_pipe(char **commands)
{
	char ***result = malloc(sizeof(char **) * (count_pipes(commands) + 2));
	int i = 0, j = 0, k = 0;

	result[i] = malloc(sizeof(char *) * (count_args(commands) + 1));
	while (commands[j])
	{
		if (ft_strcmp(commands[j], "|") == 0)
		{
			result[i][k] = NULL;
			i++;
			k = 0;
			result[i] = malloc(sizeof(char *) * (count_args(commands) + 1));
		}
		else
			result[i][k++] = commands[j];
		j++;
	}
	result[i][k] = NULL;
	result[i + 1] = NULL;
	return result;
}

int	count_pipes(char **commands)
{
	int count;

	count = 0;
	for (int i = 0; commands[i]; i++)
	{
		if (ft_strcmp(commands[i], "|") == 0)
			count++;
	}
	return (count);
}

int	contains_pipe(char **commands)
{
	for (int i = 0; commands[i]; i++)
	{
		if (ft_strcmp(commands[i], "|") == 0)
			return (1);
	}
	return (0);
}

void	free_pipeline(char ***pipeline)
{
	for (int i = 0; pipeline[i]; i++)
		free(pipeline[i]);
	free(pipeline);
}