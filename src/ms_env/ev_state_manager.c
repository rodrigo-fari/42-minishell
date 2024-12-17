/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_state_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:54:57 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/17 11:31:34 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*env_manager(t_env *env)
{
	static t_env	*static_env;

	if (env)
		static_env = env;
	return (static_env);
}

// Parametro = 0 -> Devolve o valor armazenado. (return_envs(NULL))
// Parametro = env -> Atualiza o valor armazenado. (return_envs(env))