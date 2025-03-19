/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:14:09 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/19 16:12:32 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***split_by_pipe(char **commands)
{
	char	***result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	result = malloc(sizeof(char **) * (count_pipes(commands) + 2));
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
	return (result);
}

int	count_pipes(char **commands)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

int	contains_pipe(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_pipeline(char ***pipeline)
{
	int	i;

	i = 0;
	while (pipeline[i])
	{
		free(pipeline[i]);
		i++;
	}
	free(pipeline);
}
