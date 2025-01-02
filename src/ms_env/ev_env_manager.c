/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:19:27 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/20 10:50:56 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_manager(t_env *env)
{
	static t_env	*static_env;

	if (env)
		static_env = env;
	return (static_env);
}

// Parametro = NULL -> Devolve o valor armazenado. (return_envs(NULL))
// Parametro = env -> Atualiza o valor armazenado. (return_envs(env))