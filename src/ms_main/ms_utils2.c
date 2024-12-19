/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:33:24 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/19 11:52:49 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *str, t_env *env)
{
	t_env	*head;

	if (!env || !str)
		return (NULL);
	env = env_manager(0);
	head = env;
	while (head)
	{
		if (ft_strcmp(str, head->key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	var_expand(char **user_input, t_env *env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i][0] == '$' && user_input[i][1] != '\0')
		{
			expanded = get_env_value(user_input[i] + 1, env);
			free(user_input[i]);
			user_input[i] = ft_strdup(expanded);
			free(expanded);
		}
		i++;
	}
}
