
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:14:09 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/27 19:16:17 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***allocate_pipeline(char **commands)
{
	char	***result;
	int		num_pipes;
	int		i;

	num_pipes = count_pipes(commands);
	result = malloc(sizeof(char **) * (num_pipes + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (i <= num_pipes)
	{
		result[i] = malloc(sizeof(char *) * (count_args(commands) + 1));
		if (!result[i])
			return (NULL);
		i++;
	}
	return (result);
}

void	add_command_part(char ***result, int *i, int *k)
{
	result[*i][*k] = NULL;
	(*i)++;
	*k = 0;
	result[*i] = malloc(sizeof(char *) * (count_args(NULL) + 1));
	if (!result[*i])
		return ;
}

char	***split_by_pipe(char **commands)
{
	char	***result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	result = allocate_pipeline(commands);
	if (!result)
		return (NULL);
	while (commands[j])
	{
		if (ft_strcmp(commands[j], "|") == 0)
			add_command_part(result, &i, &k);
		else
			result[i][k++] = commands[j];
		j++;
	}
	result[i][k] = NULL;
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
