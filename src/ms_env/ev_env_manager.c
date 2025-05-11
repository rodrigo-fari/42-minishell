/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:19:27 by rde-fari          #+#    #+#             */
/*   Updated: 2025/05/11 19:52:52 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Parametro = NULL -> Devolve o valor armazenado. (return_envs(NULL))
// Parametro = env -> Atualiza o valor armazenado. (return_envs(env))
t_env	*env_manager(t_env *env)
{
	static t_env	*static_env;

	if (env)
		static_env = env;
	return (static_env);
}

void	update_shell_level(void)
{
	t_env	*env;
	int		value_to_int;
	char	*value_to_char;

	value_to_int = 0;
	env = env_manager(NULL);
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			value_to_int = ft_atoi(env->value);
			value_to_int++;
			value_to_char = ft_itoa(value_to_int);
			env_update(env, "SHLVL", value_to_char, true);
		}
		env = env->next;
	}
}
