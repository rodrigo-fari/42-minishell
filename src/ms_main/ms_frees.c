/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:04:09 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/16 16:04:54 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*ft_free_envs(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		temp = env;
		env = env->next;
		free(temp);
	}
	return (0);
}
